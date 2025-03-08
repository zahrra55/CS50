from transformers import BertTokenizer, BertForSequenceClassification
import torch
import sys

# Load the pre-trained CodeBERT model
model_name = "microsoft/codebert-base"  # CodeBERT model for code analysis
tokenizer = BertTokenizer.from_pretrained(model_name)
model = BertForSequenceClassification.from_pretrained(model_name)

# Function to analyze vulnerabilities
def analyze_code_vulnerability(code_snippet):
    # Tokenize the code snippet and get input IDs
    inputs = tokenizer(code_snippet, return_tensors='pt', truncation=True, padding=True)

    # Forward pass to get model's prediction
    with torch.no_grad():
        outputs = model(**inputs)

    # Get predicted class (1: Vulnerable, 0: Secure)
    predictions = torch.argmax(outputs.logits, dim=-1)
    return predictions.item()

# Get the code snippet passed from the C program
code_snippet = sys.argv[1]  # Get the code from the command-line argument

# Analyze the code for vulnerabilities
prediction = analyze_code_vulnerability(code_snippet)
if prediction == 1:
    print("Vulnerabilities detected!")
else:
    print("Code is secure!")
