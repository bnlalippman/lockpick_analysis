import os

PATH = "/home/alippman/Lockpick/forela-criticaldata"
KEY = "bhUlIshutrea98liOp"

def encrypt(data):
    encrypted = bytearray(len(data))
    key_length = len(KEY)
    key_as_bytes = KEY.encode()
    for i in range(len(data)):
        encrypted[i] = data[i] ^ key_as_bytes[i % key_length]
    return bytes(encrypted)

def main():
    files = os.listdir(PATH)
    file_absolute_paths = [os.path.join(PATH, file) for file in files]
    for file in file_absolute_paths:
        if not file.endswith('24bes'):
            print(file)
            with open(file, "rb") as f:
                plaintext_data = f.read()

            encrypted_data = encrypt(plaintext_data)

            encrypted_file = file + '.24bes'
            print(encrypted_file)

            with open(encrypted_file, "wb") as f:
                f.write(encrypted_data)

if __name__ == '__main__':
    main()
