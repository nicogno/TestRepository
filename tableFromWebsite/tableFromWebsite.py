import requests
from bs4 import BeautifulSoup
import csv
from datetime import datetime

url="https://iscrizioni.wedosport.net/lista_iscritti.cfm?code=tre-rifugi-val-pellice-2022"
page=requests.get(url)
soup=BeautifulSoup(page.content, 'html.parser')

table = soup.find('table', attrs={'id':'classifica'})
table_body = table.find('tbody')

rows = table_body.find_all('tr')
print(len(rows))
'''
data = []
for row in rows:
    cols = row.find_all('td')
    cols = [ele.text.strip() for ele in cols]
    data.append([ele for ele in cols if ele]) # Get rid of empty values
print(data)
'''
now = datetime.now()
date_string = now.strftime("%d/%m/%Y %H:%M:%S")
list_data=[str(len(rows)), date_string]
# open the file in the 'append' mode
with open('./signed_up.csv', 'a', encoding='UTF8', newline='') as f:
    # create the csv writer
    writer = csv.writer(f)

    # write a row to the csv file
    writer.writerow(list_data)

    # close the file
    f.close()
