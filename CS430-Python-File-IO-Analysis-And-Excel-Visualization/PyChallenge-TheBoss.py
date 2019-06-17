#Steven Salmons
#UCD Data Analysis and Visualization
#Python Intro Homework

#import needed for module
import os
import csv
import datetime
import us 

#Pointer to csv of the employee data

data_csv = "employee_data2"
working_csv = os.path.join(data_csv + ".csv")

#Variables to store column data.
#I sure wouldnt want my ssn in a csv! 

employee_id =[]
first_name = []
last_name = []
dob = []
ssn = []

#Open/read the csv file start to finish,
#Using a comma to delineate column data.
#Rows stored as object type "csv" and csv
#files get stored as an array of csvs.
#A PHP version of the same task would be 
#so so much cleaner and straightforward!
 
with open(working_csv, newline = "") as csvfile:
    csvreader = csv.reader(csvfile,
   delimiter = ",")
    
    #skip header row... 
    next (csvreader)

    #Lets parse the data to standardize it
    for row in csvreader:

        
        #Build each employee ID object
        employee_id.append(row[0])


        #split and save first/last names
        
        split_name = (row[1].split())
        first_name.append(split_name[0])
        last_name.append(split_name[1])
        
        
        #DOB obj read, change format, save
        
dob.append(datetime.datetime.strptime(row[2], "%Y-%m-%d").strftime("%-m/%d/%y"))

        #Format ssn: hide full, display 4
        
        ssn_full = (row[3].split("-"))
        ssn.append("***-**-" + ssn_full[2])
        
        
    #Store a header for the new csv.
    
    clean_header = [("WWID", "First", "Last", "DOB", "SSN", "State")]
        
    #archive of all employee datatypes
    
    clean_data = zip(employee_id, first_name, last_name, dob, ssn, state)
    
    #Combine subfolder/filename as file ptr
    
    output_file = data_csv + "results.csv"
    data_output = os.path.join(output_file)
    
    #Write header, parsed data to target.
    
    with open(data_output, mode = "w", newline = "") as output
        writer = csv.writer(output)
        writer.writerows(clean_header)
        writer.writerows(clean_data)
        
#Cest fini