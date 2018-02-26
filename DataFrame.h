/*
DataFrame.h
This is the header class for the DataFrame.
Author: Tony Nguyen
Created on: 1/22/2018
Version: 1.1
*/

#include <iostream>
using namespace std;

template <class DT>
class DataFrame
{
	// Ostream operator. This helps display the contents of the row object.
	friend ostream& operator<<(ostream& output, const DataFrame<DT>& dataFrame);
protected:
	// Array of pointers to DT object.
	DT** dataRows;
	// The total number of rows.
	int noRows;
	// The total number of columns.
	int noCols;
	// Name of column in character.
	char** colNames;
public:
	/* 
	Constructor that doesn't create anything.
	*/
	DataFrame()
	{
		dataRows = NULL;
		noRows = 0;
		noCols = 0;
		colNames = NULL;
	}

	/* 
	Overloaded constructor to create the matrix of rows and columns.
	@param rows Row length passed in.
	@param cols Column length passed in.
	*/
	DataFrame(int rows, int cols)
	{
		noRows = rows;
		noCols = cols;
		colNames = new char*[noCols];
		// Creating the rows to store row objects in.
		dataRows = new DT*[noRows];
		for (int i = 0; i < noRows; i++)
		{
			// Creating the new dataRow columns with DT objects.
			dataRows[i] = new DT();

			for (int j = 0; j < noCols; j++)
			{
				// Set column names to be null initially.
				colNames[j] = NULL;
			}
		}
	}

	/* 
	Output for the program.
	*/
	void display()
	{
		// Display the column names.
		for (int i = 0; i < noCols; i++)
		{
			// In case column names is not set then print commas to prevent errors.
			if (colNames[i] == NULL)
			{
				if (i != noCols - 1)
				{
					cout << ",";
				}
				else
				{
					cout << endl;
				}
			}
			// For formatting.
			else if (i != noCols - 1)
			{
				cout << colNames[i] << ",";
			}
			else
			{
				cout << colNames[i] << endl;
			}
		}

		// Display each of the content in row objects and setting new line.
		for (int i = 0; i < noRows; i++)
		{
			cout << *dataRows[i] << endl;
		}
	}

	/* 
	Display the first n records.
	@param n Number of rows to display.
	*/
	void display(int n)
	{
		// Display the column names.
		for (int i = 0; i < noCols; i++)
		{
			// In case column names is not set then print commas to prevent errors.
			if (colNames[i] == NULL)
			{
				if (i != noCols - 1)
				{
					cout << ",";
				}
				else
				{
					cout << endl;
				}
			}
			// For formatting.
			else if (i != noCols - 1)
			{
				cout << colNames[i] << ",";
			}
			else
			{
				cout << colNames[i] << endl;
			}
		}

		// Display each of the content in row objects n times and setting new line.
		for (int i = 0; i < n; i++)
		{
			cout << *dataRows[i] << endl;
		}
	}

	/* 
	Setter for column name.
	@param col Column number.
	@param name Column name.
	*/
	void setColName(int col, const char* name)
	{
		// Adding name into constant nameHolder.
		const char *nameHolder = name;

		// Counting the size of name. It counts \0 also.
		int length = 0;
		while (*nameHolder++ != '\0')
		{
			length++;
		}

		// Creating a pointer array to copy name to.
		char *colHolder = new char[length];
		for (int i = 0; i < length; i++)
		{
			colHolder[i] = name[i];
		}
		// Adding a null character at the end of name.
		colHolder[length] = '\0';

		// Adding name to certain spot in colNames.
		colNames[col] = colHolder;
	}

	/*
	Get the ith row.
	@return Address for rows at position i.
	*/
	DT& operator[] (int i)
	{
		return *dataRows[i];
	}

	/* 
	Get the array of pointers to column names.
	@return colNames Column name pointers.
	*/
	char** getColNames()
	{
		return colNames;
	}

	/*
	Get the number of rows.
	@return noRows Row length.
	*/
	int getNumberRows()
	{
		return noRows;
	}

	/* 
	Returns rows and display the update on the screen.
	@param rows Pointer of row numbers to create in new table.
	@param rLen Number of rows to create.
	*/
	DataFrame<DT>* getRows(int* rows, int rLen)
	{
		// Create a new DataFrame to return of rows.
		DataFrame<DT>* tempRow = new DataFrame<DT>(rLen, noCols);

		for (int i = 0; i < rLen; i++)
		{
			// Populating the rows.
			(*tempRow)[i] = *dataRows[rows[i]];

			for (int j = 0; j < noCols; j++)
			{
				// Setting column names into tempRow.
				(*tempRow).setColName(j, colNames[j]);
			}
		}

		return tempRow;
	}

	/* 
	Add a new row at the last row.
	@param newRow Memory address of the type DT to add to dataRows.
	*/
	void addRow(DT& newRow)
	{
		// Creating a new dataRows to add another object in.
		DT** newDataRows = new DT*[noRows + 1];

		// Copy over row objects.
		for (int i = 0; i < noRows; i++)
		{
			newDataRows[i] = dataRows[i];
		}
		// Add newRow into the end of dataRows.
		newDataRows[noRows] = new DT();
		*newDataRows[noRows] = newRow;

		// Delete old dataRow pointers.
		delete[] dataRows;

		// Adding contents of new dataRows into old dataRows after deleting its old row objects.
		dataRows = newDataRows;

		// Incrementing number of rows.
		noRows++;
	}

	/* 
	Remove the ith row.
	@param i Row number to remove.
	*/
	void removeRow(int i)
	{
		// Creating a new dataRows to remove an object.
		DT** newDataRows = new DT*[noRows - 1];

		// Copy over old dataRows to new dataRows until we hit the index to delete.
		for (int j = 0; j < i; j++)
		{
			newDataRows[j] = dataRows[j];
		}
		// If we hit the index then skip over it and move on.
		for (int j = i; j < noRows; j++)
		{
			newDataRows[j] = dataRows[j + 1];
		}

		// Delete old dataRow pointers.
		delete[] dataRows;

		// Adding new dataRows back to old dataRows.
		dataRows = newDataRows;

		// Decreasing row size.
		noRows--;
	}

	/* 
	Add row at the specified position.
	@param position Index to place it at.
	@param newRow New row to place.
	*/
	void insertRow(int position, DT& newRow)
	{
		// Creating a new dataRows to add another object in.
		DT** newDataRows = new DT*[noRows + 1];

		// Copy over old dataRows to new dataRows until we hit the index to delete.
		for (int i = 0; i <= position; i++)
		{
			if (i != position)
			{
				newDataRows[i] = dataRows[i];
			}
			else
			{
				newDataRows[i] = new DT();
				*newDataRows[i] = newRow;
			}
		}
		// Shifting over all elements while copying over.
		for (int i = position; i < noRows; i++)
		{
			newDataRows[i + 1] = dataRows[i];
		}

		// Delete the old dataRow pointers.
		delete[] dataRows;

		// Adding contents of new dataRows into old dataRows after deleting its old row objects.
		dataRows = newDataRows;

		// Incrementing number of rows.
		noRows++;
	}

	/*
	Write the ostream operator. For displaying the object's content.
	@param ostream &output The object's content in format.
	@param RowObject &row The dataFrame with row objects to display.
	@return output The address for dataFrame with row objects to display.
	*/
	template <class DT>
	ostream& operator<<(ostream& output, const DataFrame<DT>& dataFrame)
	{
		for (int i = 0; i < dataFrame.noRows; i++)
		{
			output << dataFrame.dataRows[i];
		}
		return output;
	}

	/*
	Deconstructor.
	*/
	~DataFrame()
	{
		// If table exist then delete it.
		if (dataRows != NULL)
		{
			// Delete the table. This functions fine.
			for (int i = 0; i < noRows; i++)
			{
				dataRows[i] = NULL;
				delete[] dataRows[i];
			}
			delete[] dataRows;

			// If colNames exist then delete it.
			if (colNames != NULL)
			{
				for (int i = 0; i < noCols; i++)
				{
					colNames[i] = NULL;
					delete[] colNames[i];
				}
				delete[] colNames;
			}
			// Setting row and column to 0.
			noRows = 0;
			noCols = 0;
		}
	}
};
