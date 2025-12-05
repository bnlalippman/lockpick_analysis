import os

PATH = "/home/alippman/Lockpick/forela-criticaldata"
KEY = "bhUlIshutrea98liOp"

def decrypt(data):
    # An array of ints 0-255 to represent
    decrypted = bytearray(len(data))
    # Get length of our decryption key
    key_length = len(KEY)
    # Create our key as a byte string
    key_as_bytes = KEY.encode()
    
    # For byte in data 
    for byte in range(len(data)):
        # Take each byte of file data and XOR by each key byte
        # The modulo (%) is used to jump back to beginning of key
        decrypted[byte] = data[byte] ^ key_as_bytes[byte % key_length]
    return bytes(decrypted)

def main():
    # Gather list of absolute paths for files under PATH
    files = os.listdir(PATH)
    file_absolute_paths = [os.path.join(PATH, file) for file in files]
    
    # Iterate over each file
    for file in file_absolute_paths:
        # If encrypted
        if file.endswith('24bes'):
            print(f'[*] Decrypting {file}')
            # Open and read encrypted file in binary read mode
            with open(file, "rb") as f:
                encrypted_data = f.read()
            
            # Decrypt data using our XOR function
            plaintext = decrypt(encrypted_data)

            # Strip the encrypted file extension before writing out
            decrypted_file = file.strip('.24bes')

            # Write out the decrypted binary data to new file
            with open(decrypted_file, "wb") as f:
                f.write(plaintext)
            print(f'[+] Decrypted {decrypted_file}')

if __name__ == '__main__':
    main()
