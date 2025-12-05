import os

PATH = "/path/to/files"
KEY = "bhUlIshutrea98liOp"

def encrypt(data):
    # An array of ints 0-255 to represent
    encrypted = bytearray(len(data))
    # Get length of our encryption key
    key_length = len(KEY)
    # Create our key as a byte string
    key_as_bytes = KEY.encode()
    
    # For byte in data 
    for byte in range(len(data)):
        # Take each byte of file data and XOR by each key byte
        # The modulo (%) is used to jump back to beginning of key
        encrypted[byte] = data[byte] ^ key_as_bytes[byte % key_length]
    return bytes(encrypted)

def main():
    # Gather list of absolute paths for files under PATH
    files = os.listdir(PATH)
    file_absolute_paths = [os.path.join(PATH, file) for file in files]
    
    # Iterate over each file
    for file in file_absolute_paths:
        # If file ends in txt
        if file.endswith('txt'):
            print(f'[*] Encrypting {file}')
            # Open and read encrypted file in binary read mode
            with open(file, "rb") as f:
                encrypted_data = f.read()
            
            # Encrypt data using our XOR function
            plaintext = encrypt(encrypted_data)

            # Strip the encrypted file extension before writing out
            encrypted_file = file.strip('.24bes')

            # Write out the encrypted binary data to new file
            with open(encrypted_file, "wb") as f:
                f.write(plaintext)
            print(f'[+] Encrypted {encrypted_file}')

if __name__ == '__main__':
    main()
