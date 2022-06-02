import requests
from bs4 import BeautifulSoup

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
