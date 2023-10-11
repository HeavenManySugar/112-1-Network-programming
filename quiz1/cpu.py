import requests
from bs4 import BeautifulSoup

url = 'https://www.intel.com.tw/content/www/tw/zh/products/sku/230490/intel-core-i713700-processor-30m-cache-up-to-5-20-ghz/specifications.html'
response = requests.get(url)
soup = BeautifulSoup(response.text, 'html.parser')
data = soup.find_all('div', class_='col-xs-6 col-lg-6 tech-data')
print(f'處理器編號: {data[3].text.strip()}')
print(f'核心數量: {data[7].text.strip()}')
print(f'最大超頻: {data[11].text.strip()}')
print(f'快取記憶體: {data[17].text.strip()}')
print(f'推出日期: {data[22].text.strip()}')
print(f'最大記憶體大小: {data[25].text.strip()}')
print(f'處理器繪圖: {data[30].text.strip()}')
print(f'繪圖基頻: {data[31].text.strip()}')
