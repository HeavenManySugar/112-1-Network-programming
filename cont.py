import xml.etree.ElementTree as ET
import json

tree = ET.parse('cont.xml')
root = tree.getroot()

for item in root.iter("country"):
    if item.attrib['name'] == "愛爾蘭":
        item.find("gdppc").text = "88888"
    if item.attrib['name'] == "新加坡":
        item.append(ET.Element("neighbor", {"name": "亞特蘭提斯", "direction": "南"}))
        
tree.write("cont2.xml", encoding="utf-8")

tree2 = ET.ElementTree(file='cont2.xml')
root2 = tree2.getroot()

for country in root.iter("country"):
    print(country.attrib["name"], end=": ")
    for neighbor in country.iter("neighbor"):
        print(neighbor.attrib["name"], end=" ")
    print()
    for neighbor in country.findall("neighbor"):
        print(f'{neighbor.attrib["name"]}: {country.attrib["name"]}')
