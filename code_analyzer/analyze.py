from transformers import RobertaTokenizer, RobertaForSequenceClassification
import torch
import time
import os
import argparse
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas
from flask import Flask, request, render_template
import warnings
import logging
import datetime

# Suppress model initialization warning
warnings.filterwarnings("ignore", message="Some weights of RobertaForSequenceClassification were not initialized")
logging.getLogger("transformers.modeling_utils").setLevel(logging.ERROR)

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# Load fine-tuned model and tokenizer
MODEL_NAME = "huggingface/CodeBERTa-small-v1"  # Path to your fine-tuned model
try:
    tokenizer = RobertaTokenizer.from_pretrained(MODEL_NAME)
    model = RobertaForSequenceClassification.from_pretrained(MODEL_NAME)
    logging.info("Model and tokenizer loaded successfully.")
except Exception as e:
    logging.error(f"Error loading model or tokenizer: {e}")
    raise

def detect_language(file_path):
    """
    Detect the programming language based on the file extension.
    """
    _, ext = os.path.splitext(file_path)
    if ext in ['.c', '.h']:
        return 'c'
    elif ext in ['.py']:
        return 'python'
    # Add more languages and their extensions as needed
    else:
        return 'unknown'

def analyze_code_vulnerability(code_snippet, language):
    """
    Analyze code snippet for vulnerabilities using the fine-tuned model.
    """
    try:
        # Explicitly check for known vulnerabilities
        vulnerabilities = {
            'c': ["gets(", "strcpy("],
            'python': ["eval(", "exec("]
        }
        if language in vulnerabilities:
            for vuln in vulnerabilities[language]:
                if vuln in code_snippet:
                    logging.info(f"Detected vulnerability: {vuln}")
                    return 1  # Vulnerability detected

        # Use the model to analyze the code snippet
        inputs = tokenizer(code_snippet, return_tensors='pt', truncation=True, padding=True, max_length=512)
        with torch.no_grad():
            outputs = model(**inputs)
        prediction = torch.argmax(outputs.logits, dim=-1).item()
        logging.info(f"Prediction: {prediction}")
        return prediction
    except Exception as e:
        logging.error(f"Error analyzing code snippet: {e}")
        return None

def suggest_fix(code_snippet, language):
    """
    Suggest fixes for common vulnerabilities based on the language.
    """
    fixes = {
        'c': {
            "gets(": "fgets(input, sizeof(input), stdin);",
            "strcpy(": "strncpy(buffer, input, sizeof(buffer) - 1); buffer[sizeof(buffer) - 1] = '\\0';"
        },
        'python': {
            "eval(": "# Avoid using eval; consider safer alternatives like ast.literal_eval\n",
            "exec(": "# Avoid using exec; consider safer alternatives\n"
        }
        # Add more languages and their fixes as needed
    }
    fixed_code = code_snippet
    if language in fixes:
        for vuln, fix in fixes[language].items():
            if vuln in code_snippet:
                fixed_code = fixed_code.replace(vuln, fix)
    return fixed_code

def generate_security_report(filename, code, prediction, execution_time, fixed_code=None):
    """
    Generate a PDF security report using reportlab.
    """
    try:
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        pdf_path = f"{filename}_security_report_{timestamp}.pdf"
        c = canvas.Canvas(pdf_path, pagesize=letter)
        c.setFont("Helvetica", 12)
        c.drawString(72, 750, "Code Security Analysis Report")
        c.drawString(72, 730, f"File: {filename}")
        c.drawString(72, 710, f"Execution Time: {execution_time:.4f} seconds")
        c.drawString(72, 690, "Analyzed Code:")

        # Adjust the starting position for the code block
        y_position = 670
        line_height = 14  # Adjust line height as needed

        # Split the code into lines and draw each line
        for line in code[:1000].split('\n'):  # Truncate long code
            c.drawString(72, y_position, line)
            y_position -= line_height

        if prediction == 1:
            c.setFillColorRGB(1, 0, 0)  # Red
            c.drawString(72, y_position - line_height, "⚠️  Vulnerabilities detected!")
            c.setFillColorRGB(0, 0, 0)  # Black
            c.drawString(72, y_position - 2 * line_height, "🔴 Vulnerability detected in the code.")
            if fixed_code:
                c.drawString(72, y_position - 3 * line_height, "✅ Recommended Fix:")
                y_position -= 4 * line_height
                for line in fixed_code[:1000].split('\n'):  # Truncate long code
                    c.drawString(72, y_position, line)
                    y_position -= line_height
        else:
            c.setFillColorRGB(0, 0.5, 0)  # Green
            c.drawString(72, y_position - line_height, "✅ Code is secure!")

        c.save()
        logging.info(f"Analysis report saved to {pdf_path}")
    except Exception as e:
        logging.error(f"Error generating security report: {e}")

def analyze_files(file_paths):
    """
    Analyze multiple files for vulnerabilities.
    """
    for file_path in file_paths:
        if os.path.exists(file_path):
            try:
                with open(file_path, "r") as f:
                    code = f.read()
                language = detect_language(file_path)
                logging.info(f"Detected language: {language}")
                start_time = time.time()
                prediction = analyze_code_vulnerability(code, language)
                execution_time = time.time() - start_time
                if prediction is not None:
                    fixed_code = suggest_fix(code, language) if prediction == 1 else None
                    generate_security_report(file_path, code, prediction, execution_time, fixed_code)
                else:
                    logging.error(f"Failed to analyze file: {file_path}")
            except Exception as e:
                logging.error(f"Error reading file {file_path}: {e}")
        else:
            logging.error(f"File not found: {file_path}")

def interactive_cli():
    """
    Interactive CLI for analyzing code snippets.
    """
    while True:
        code_snippet = input("Enter your code (or type 'exit' to quit): ")
        if code_snippet.lower() == 'exit':
            break
        language = input("Enter the language (e.g., 'c', 'python'): ").strip().lower()
        start_time = time.time()
        prediction = analyze_code_vulnerability(code_snippet, language)
        execution_time = time.time() - start_time
        if prediction is not None:
            print(f"Execution Time: {execution_time:.4f} seconds")
            if prediction == 1:
                print("⚠️  Vulnerabilities detected!")
                fixed_code = suggest_fix(code_snippet, language)
                print("Suggested Fix:")
                print(fixed_code)
                apply_fix = input("Apply Fix? [Y/N]: ").strip().lower()
                if apply_fix == 'y':
                    code_snippet = fixed_code
                    print("Fix applied.")
            else:
                print("✅ Code is secure!")
        else:
            print("Error analyzing code snippet.")

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    """
    Flask web interface for analyzing code.
    """
    if request.method == "POST":
        code = request.form["code"]
        language = request.form["language"]
        start_time = time.time()
        prediction = analyze_code_vulnerability(code, language)
        execution_time = time.time() - start_time
        result = "⚠️  Vulnerabilities detected!" if prediction == 1 else "✅ Code is secure!"
        fixed_code = suggest_fix(code, language) if prediction == 1 else None
        return render_template("index.html", execution_time=execution_time, result=result, code=code, fixed_code=fixed_code)
    return render_template("index.html")

def main():
    """
    Main function to handle command-line arguments.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("files", nargs='*', help="File paths to analyze")
    parser.add_argument("--cli", action="store_true", help="Start interactive CLI mode")
    parser.add_argument("--web", action="store_true", help="Start web UI")
    args = parser.parse_args()

    if args.cli:
        interactive_cli()
    elif args.web:
        app.run(debug=True)
    elif args.files:
        analyze_files(args.files)
    else:
        print("No input provided. Use --cli, --web, or specify file paths.")

if __name__ == "__main__":
    main()
