import xml.etree.ElementTree as ET
import requests

# 下載xml檔案
url = 'https://data.ntpc.gov.tw/api/datasets/3c6411d8-57be-462c-add4-046d86bf5de4/xml/preview'
r = requests.get(url)
with open('data1.xml', 'wb') as f:
    f.write(r.content)

# 讀取xml檔案
tree = ET.parse('data1.xml')
root = tree.getroot()

# 步驟1：將seqno : 23 資訊改為 25
for row in root.findall('row'):
    seqno = row.find('seqno')
    if seqno.text == '23':
        seqno.text = '25'

# 步驟2：新增一個row
new_row = ET.SubElement(root, 'row')
ET.SubElement(new_row, 'type').text = '一般路線'
ET.SubElement(new_row, 'seqno').text = '24'
ET.SubElement(new_row, 'agency_codes').text = '382290000H'
ET.SubElement(new_row, 'routename').text = '999'
ET.SubElement(new_row, 'start_and_end').text = '光華路口-北科校園'
ET.SubElement(new_row, 'weekday_operation_hours').text = '去程：0600-2100；返程：0600-2100'
ET.SubElement(new_row, 'holiday_operation_hours').text = '去程：0600-1630；返程：0640-1710'

# 步驟3：將上述兩步修改後的資料寫入data2.xml
tree.write('data2.xml')

# 步驟4：讀取data2.xml，篩選出去程的時間為6點到21點且返程時間為6點到21點的一般路線資訊。
tree2 = ET.parse('data2.xml')
root2 = tree2.getroot()

result = []
for row in root2.findall('row'):
    type_ = row.find('type').text
    seqno = row.find('seqno').text
    routename = row.find('routename').text
    start_and_end = row.find('start_and_end').text
    weekday_operation_hours = row.find('weekday_operation_hours').text

    if type_ == "一般路線" and "去程：0600-2100；返程：0600-2100" in weekday_operation_hours:
        result.append((int(seqno), routename, start_and_end))

# 依照seqno進行排序並輸出結果
result.sort()
print('seqno routename start_and_end')
for r in result:
    print(f"{r[0]} {r[1]} {r[2]}")
