#include <stdio.h>
#include "csv_parser.h"

int main()
{
	CSVParser parser ;
	string file_path = "lala.csv";
	parser.CsvFileToBitmap(file_path);

}