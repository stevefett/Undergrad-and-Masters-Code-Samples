#Steven Salmons
#LeBanc
#UCD Data Analysis Python Assgn Part 2
#Performing worldsaving bank math on csvz


#Load Playing with cli file I/O, csv
#csv storigot parsingrow/column csv data
#Basic Math ieperistent variables, avg
#month to month revenue delta, including
#greatest, worst, and avg delta


#And we are off

import modules
import os
import csv


#Tell user to input target csv file 
#without the .csv suffix that the csv.
#file must be in current working dir

print("Pay attention to current Working    directory. Typos require restart.")
    
    

input_csv = input("Enter dsired csv    filename to be analyzed.  Do not include     extension - ie enter bank.csv as bank:   ")


#Store, process csv contents into
#csvreader, set by delimiter and newline

working_csv = os.path.join(input_csv + ".csv")


#Loop through commacolumns when tallying
#totals and deltas, gong thru rows based on
#EOL char newline until EoF is reached.

loaded data
with open(working_csv, newline = "") as csvfile:
    csvreader = cs.reader(csvfile, delimiter = ",")
    next(csvreader, None)
    
    #set variables to track
    total_months = 0
    total_revenue = 0
    prev_revenue = 0
    avg_revenue_change = 0
    revenue_change = 0
    greatest_increase = 0
    greatest_decrease = 0
    greatest_increase_month = " "
    greatest_decrease_month = " "

    #Tally each rows info for all roww
    for row in csvreader:
        
        #total months
        total_months = total_months + 1

        #total revenue
        total_revenue = total_revenue + int(row[1])

        #monthly revenue change
        revenue_change = int(row[1]) - prev_revenue

        #average revenue change
        avg_revenue_change = (int(row[1]) - prev_revenue) + avg_revenue_change

        # greatest increase in revenue
        if revenue_change >        greatest_increase:
            greatest_increase =             revenue_change
            greatest_increase_month =             row[0]

        #determine greatest decreases in revenue
        if revenue_change < greatest_decrease:
            greatest_decrease = revenue_change
            greatest_decrease_month = row[0]

        #reset theprevious revenue
        prev_revenue = int(row[1])

#calculate average delta per month
    for row in csvreader:
        #calculate total months
        total_months = total_months + 1

        #calculate total revenue
        total_revenue = total_revenue +             int(row[1])
        #calcuate monthly revenue delta
        revenue_change = int(row[1]
        prev_revenueeper hits EOR

        #calculate average revenue delta
        avg_revenue_change = (int(row[1]) - prev_revenue) + avg_revenue_change

        #determine greatest positive delta
        if revenue_change >  greatest_increase:
            greatest_increase = revenue_change
            greatest_increase_month = row[0]

        #determine greatest decreases in revenue
        if revenue_change < greatest_decrease:
            greatest_decrease = revenue_change
            greatest_decrease_month = row[0]

        #reset previous revenue
        prev_revenue = int(row[1])

#calculate average delta per month
avg_revenue_change = avg_revenue_change/.  total_months


#Set money format, print results to the cli
print(" ")
print("Fiscal Accunt Performance")
print("------------------")
print("Total Months: " + str(total_months))
print("Total Revenue: $" + format(total_revenue, ',.2f'))
print("Average Revenue Change: $" + format(avg_revenue_change, ',.2f'))
print("Greatest Increase in Revenue: " + greatest_increase_month + "($" + format(greatest_increase, ',.2f') +")")
print("Greatest decrease in Revenue: " + greatest_decrease_month + "($" + format(greatest_decrease, ',.2f')+ ")")


#Create a new file, using the csv name as
#the first part of the prefix and .txt 
.
results_file = (input_csv + "_results.txt")

with open(results_file, "w", newline="") as results:
    txtwriter = csv.writer(results)
