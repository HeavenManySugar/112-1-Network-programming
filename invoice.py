from __future__ import unicode_literals, print_function
import urllib
from bs4 import BeautifulSoup
import urllib.request

prize_numbers = []
request_url = 'http://invoice.etax.nat.gov.tw/'  # 財政部官網
htmlContent = urllib.request.urlopen(request_url).read()  # 開啟網址取得HTML
soup = BeautifulSoup(htmlContent, "html.parser")  # 以"html.parser"解析設為soup物件
# 用soup的find_all找網頁所有標籤為"span"且class屬性值為"font-weight-bold etw-color-red"與"font-weight-bold"的內容,設給result物件
results = soup.find_all(
    "span", {"class": {"font-weight-bold etw-color-red", "font-weight-bold"}})
subTitle = ['特別獎', '特獎', '頭獎']  # 獎項
# for index, item in enumerate(results[:2]):
#     print('>> {0} : {1}'.format(subTitle[index], item.text))
for index2, item2 in enumerate(results[2:8]):
    if index2 % 2 == 0:
        # print('>> {0} : {1}'.format(subTitle[2], item2.text), end='')
        pass
    else:
        # print(item2.text)
        prize_numbers.append(item2.text)

while (True):
    userInput = input()
    result = 0
    for number in prize_numbers:
        tmp = 0
        for i in range(1, 4):
            if userInput[-i] == number[-i]:
                tmp += 1
        result = max(result, tmp)
    if result == 3:
        print("中二百元")
    elif result == 2:
        print("差一個號碼中兩百元")
