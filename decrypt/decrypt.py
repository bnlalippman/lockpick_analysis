import os

PATH = "/home/alippman/Lockpick/forela-criticaldata"
KEY = "bhUlIshutrea98liOp"

def decrypt(data):
    decrypted = bytearray(len(data))
    key_length = len(KEY)
    key_as_bytes = KEY.encode()
    for i in range(len(data)):
        decrypted[i] = data[i] ^ key_as_bytes[i % key_length]
    return bytes(decrypted)

def main():
    files = os.listdir(PATH)
    file_absolute_paths = [os.path.join(PATH, file) for file in files]
    for file in file_absolute_paths:
        if file.endswith('24bes'):
            print(file)
            with open(file, "rb") as f:
                encrypted_data = f.read()
            
            plaintext = decrypt(encrypted_data)

            decrypted_file = file.strip('.24bes')
            print(decrypted_file)

            with open(decrypted_file, "wb") as f:
                f.write(plaintext)

if __name__ == '__main__':
    main()
