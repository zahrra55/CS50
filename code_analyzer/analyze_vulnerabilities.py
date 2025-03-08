from transformers import RobertaTokenizer, RobertaForSequenceClassification
import torch
import sys
import json
import re
import warnings
import transformers
import logging

# Suppress warnings
warnings.filterwarnings("ignore", category=UserWarning, module="transformers")

# Suppress all stderr output from transformers (last resort)
sys.stderr = open('/dev/null', 'w')

# Disable specific transformer warnings
transformers.logging.set_verbosity_error()
logging.getLogger("transformers").setLevel(logging.ERROR)

# Suppress model warnings
warnings.filterwarnings("ignore")

# Load the pre-trained CodeBERT model
model_name = "microsoft/codebert-base"
tokenizer = RobertaTokenizer.from_pretrained(model_name)
model = RobertaForSequenceClassification.from_pretrained(model_name)

# Define common vulnerabilities and fixes
VULNERABILITY_FIXES = {
    r"\bgets\s*\(": {
        "issue": "Buffer overflow risk due to unsafe `gets()` usage.",
        "fix": "Use `fgets(buffer, sizeof(buffer), stdin);` instead."
    },
    r"\bstrcpy\s*\(": {
        "issue": "Potential buffer overflow with `strcpy()`.",
        "fix": "Use `strncpy(dest, src, n)` and ensure `n` is within bounds."
    },
    r"\bsprintf\s*\(": {
        "issue": "Buffer overflow risk with `sprintf()`.",
        "fix": "Use `snprintf(dest, size, format, args...)` instead."
    },
    r"\bsystem\s*\(": {
        "issue": "Command injection risk with `system()`.",
        "fix": "Use `execvp()` or similar safer alternatives."
    }
}

# Function to analyze code vulnerabilities
def analyze_code_vulnerability(code_snippet):
    inputs = tokenizer(code_snippet, return_tensors="pt", truncation=True, padding=True)

    with torch.no_grad():
        outputs = model(**inputs)

    prediction = torch.argmax(outputs.logits, dim=-1).item()

    # Identify specific vulnerabilities using regex
    detected_vulnerabilities = []
    for pattern, details in VULNERABILITY_FIXES.items():
        if re.search(pattern, code_snippet):
            detected_vulnerabilities.append({"vulnerability": details["issue"], "fix": details["fix"]})

    return prediction, detected_vulnerabilities

# Read input code snippet from command-line argument
code_snippet = sys.argv[1] if len(sys.argv) > 1 else ""
if not code_snippet:
    print("Error: No code snippet provided!")
    sys.exit(1)

# Analyze the code
prediction, vulnerabilities = analyze_code_vulnerability(code_snippet)

# Generate output
output_report = {"code_snippet": code_snippet, "prediction": "Vulnerable" if prediction == 1 else "Secure"}

if vulnerabilities:
    output_report["vulnerabilities"] = vulnerabilities
    print("\n⚠️  Vulnerabilities detected!\n")
    for issue in vulnerabilities:
        print(f"🔴 {issue['vulnerability']}")
        print(f"✅ Recommended Fix: {issue['fix']}\n")
else:
    print("\n✅ Code is secure!\n")

# Save results to a file
with open("security_report.txt", "w") as f:
    f.write(json.dumps(output_report, indent=4))

print("📄 Analysis report saved to security_report.txt")
