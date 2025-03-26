from cs50 import get_int
# Keep asking antil the number is valid!
while True:
    Height = get_int("Height: ")
    if Height in range(1, 9):
        break
# Print your Paradym >>
for i in range(Height):
    print(' ' * (Height-(i+1)) + '#'*(i+1) + '  ' + '#'*(i+1))
