import requests #匯入套件
from bs4 import BeautifulSoup #解析網頁

html = requests.get("https://rate.bot.com.tw/xrt?Lang=zh-TW") #回傳HTML檔案,轉存html物件
bsObj = BeautifulSoup(html.content, "lxml") #解析網頁,建立bs物件

result = []

for single_tr in bsObj.find("table", {"title":"牌告匯率"}).find("tbody").findAll("tr"): #針對匯率表格分析
    cell = single_tr.findAll("td") #找到每一個表格
    currency_name = cell[0].find("div", {"class":"visible-phone"}).contents[0] #找到表格中幣別
    currency_name = currency_name.replace("\r","") #取代不需要的字元
    currency_name = currency_name.replace("\n","")
    currency_name = currency_name.replace(" ","")
    currency_rate_buy = str(cell[1].contents[0]) #找到幣別匯率
    currency_rate_sell = str(cell[2].contents[0]) #找到幣別匯率
    if currency_rate_sell != '-' and currency_rate_buy != '-':
        result.append([float(currency_rate_sell)-float(currency_rate_buy), currency_name])

result.sort(reverse=True)
for i in range(3):
    print(result[i][1], result[i][0])