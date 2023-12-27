# Bootloader Block Parser Algorithm:
It parses a block of data of the sent Hex file (64 records at a time).
## its Functions:
- validates the records through checking the checksum byte of each record.
- Extracts all the data of each record and classifies it according to their type.
- Parses all the data to be flashed and stores it in data array.
- returns the needed data as : high address + low address of each record + record data part in a pointer to struct.

### This is the result:
 ![alt text](https://github.com/blue409/FOTA_NTI_GraduationProject/blob/main/UART_Bootloader_ARM/BL_Algo_Block/Result.JPG)
