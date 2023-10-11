from __future__ import unicode_literals, print_function
import urllib
from bs4 import BeautifulSoup
import urllib.request

prize_numbers = []
prize_description = []
subTitle = ['特別獎', '特獎', '頭獎']  # 獎項
request_url = ('https://www.etax.nat.gov.tw/etw-main/ETW183W2_11201/', 'https://www.etax.nat.gov.tw/etw-main/ETW183W2_11203/', 'https://www.etax.nat.gov.tw/etw-main/ETW183W2_11205/', 'https://www.etax.nat.gov.tw/etw-main/ETW183W2_11207/')  # 財政部官網
for i in range(4):
    tmp = {}
    htmlContent = urllib.request.urlopen(request_url[i]).read()  # 開啟網址取得HTML
    soup = BeautifulSoup(htmlContent, "html.parser")  # 以"html.parser"解析設為soup物件
    # 用soup的find_all找網頁所有標籤為"span"且class屬性值為"font-weight-bold etw-color-red"與"font-weight-bold"的內容,設給result物件
    for description in soup.find_all("td", {"style": {"text-align: center;"}}):
        prize_description.append(description.text)
    results = soup.find_all("div", {"class": {"col-12 mb-3"}})
    for title in subTitle:
        tmp[title] = []
    for index, item in enumerate(results[:2]):
        tmp[subTitle[index]].append(item.text.strip())
    for index2, item2 in enumerate(results[2:8]):
        tmp[subTitle[2]].append(item2.text.strip())
    prize_numbers.append(tmp)
    prize_numbers.append(tmp)

prize_money = [10000000, 200000, 40000]
I = []
for i in range(int(input())):
    total = 0
    tmp = input()
    I.append(tmp)

month = int(input())

for userInput in I:
    flag = 1
    for key, value in prize_numbers[month-1].items():
        # print(userInput, value)
        if userInput in value:
            index = subTitle.index(key)
            print(f'{userInput} {key} {prize_money[index]} {prize_description[index]}')
            total += prize_money[index]
            flag = 0
            break
    if flag:
        value = prize_numbers[month-1]['頭獎']
        for tmp in range(len(value)):
            # print(userInput, value[tmp])
            cnt = 0
            for i in range(1, 9):
                if userInput[-i] == value[tmp][-i]:
                    cnt += 1
                else:
                    break
            # print(cnt)
            if cnt == 3:
                print(f'{userInput} 六獎 200 {prize_description[7]}')
                total += 200
            elif cnt == 4:
                print(f'{userInput} 五獎 1000 {prize_description[6]}')
                total += 1000
            elif cnt == 5:
                print(f'{userInput} 四獎 4000 {prize_description[5]}')
                total += 4000
            elif cnt == 6:
                print(f'{userInput} 三獎 10000 {prize_description[4]}')
                total += 10000
            elif cnt == 7:
                print(f'{userInput} 二獎 40000 {prize_description[3]}')
                total += 40000
print(total)