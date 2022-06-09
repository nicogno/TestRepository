import requests
from bs4 import BeautifulSoup
import csv
from datetime import datetime

url="https://iscrizioni.wedosport.net/lista_iscritti.cfm?code=tre-rifugi-val-pellice-2022"
page=requests.get(url)
soup=BeautifulSoup(page.content, 'html.parser')

table = soup.find('table', attrs={'id':'classifica'})
table_body = table.find('tbody')

############ Total lines

rows = table_body.find_all('tr')
print("Participants "+str(len(rows)))

now = datetime.now()
date_string = now.strftime("%d/%m/%Y %H:%M:%S")
list_data = [str(len(rows)), date_string]
# open the file in the 'append' mode
with open('./signed_up.csv', 'a', encoding='UTF8', newline='') as f:
    # create the csv writer
    writer = csv.writer(f)
    # write a row to the csv file
    writer.writerow(list_data)
    # close the file
    f.close()

############ New participants

current_data = []   # Data from webpages
for row in rows:
    cols = row.find_all('td')
    cols = [ele.text.strip() for ele in cols]
    part = str(cols[1] + ' ' + cols[2])
    current_data.append(part)

file = open('participants.csv')   # Existing data
csvreader = csv.reader(file)
oldrows = []
for row in csvreader:
    oldrows.append(row[0])  # Needs[0] otherwise is a list itself
file.close()

with open('./participants.csv', 'a', encoding='UTF8', newline='') as f1:
    # create the csv writer
    writer = csv.writer(f1)
    # write a row to the csv file
    print("New entries:")
    for row in current_data:
        if row not in oldrows:
            writer.writerow([row, now])  # [] needed to get string instead of chars
            print(row)
    # close the file
    f1.close()
