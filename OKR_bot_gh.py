
# Lance Gartrell
# Bot designed to populate an excel sheet with clients--work exclusively with tigernet database
# + emailing feature
#
#
# imports needed to install via terminal/console
#    - pip install pygsheets
#    - pip install gspread
#    - pip install oauth2client
#    - pip install pandas
#    - pip3 install pandas - -upgrade
#

# imports mainly for the chrome driver and html interaction
from selenium import webdriver
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.by import By
import time
import smtplib
from email.message import EmailMessage

# for web scraping
from urllib.request import urlopen
from bs4 import BeautifulSoup
import requests

# for excel
from openpyxl import worksheet
import openpyxl
import pandas as pd
import xlsxwriter

# for google sheets
import pygsheets
import gspread
from oauth2client.service_account import ServiceAccountCredentials
from gspread_dataframe import set_with_dataframe
import gspread_dataframe as gd

# for csv
import csv
from selenium.common.exceptions import NoSuchElementException

def find_loc(headers):
    loc = 0
    for header in headers: 
        loc += 1
        h = header.get_attribute('innerHTML')
        if h == "Career Information":
            header.click()
            return True
    return False

def convert(string):
    li = list(string.split(": "))
    return li

 
# Ask the user to input the targeted country, state, city, and year in the tigernet database

search_year = input("Please enter the year you wish to search for: \n")
time.sleep(1)
print(f'You entered {search_year}')
search_country = input("Please enter the country you wish to search for: \n")
print(f"You entered {search_country}")
time.sleep(1)
search_state = input("Please enter the 2 character state code you wish to search for: \n")
print(f"You entered {search_state}")
time.sleep(1)
search_city = input("Please enter the city you wish to search for: \n")
print(f"You entered {search_city}")
search_major = input("Please enter the major you wish to search for: \n")
time.sleep(1)
print(f'You entered {search_major}')

if search_city:
    search_city = search_city
else: 
    search_city == "null"

if search_state:
    search_state = search_state
else: 
    search_state == "null"

if search_country:
    search_country = search_country
else: 
    search_country == "null"



# Allows for the bot to login and move through the html of websites
options = webdriver.ChromeOptions()
options.add_experimental_option('excludeSwitches', ['enable-logging'])
driver = webdriver.Chrome(options=options)

#  opens tigernet
driver.get("https://tigernet.princeton.edu/s/1760/02-tigernet/20/interior.aspx?sid=1760&gid=2&pgid=6#/Search/Advanced")

# Maximize the window and let code stall
# for 10s to properly maximise the window.
driver.maximize_window()
time.sleep(5)

# Obtain button by link text and click.
firstLoginButton = driver.find_element(By.ID, "cid_40_btnSsoLogin")
firstLoginButton.click()
time.sleep(3)


# Second log in screen, types in info and logs in
username = driver.find_element(By.ID, "username").send_keys("*****")
time.sleep(2)
password = driver.find_element(By.ID, "password").send_keys("*********")
time.sleep(2)
second_search_button = driver.find_element(By.CLASS_NAME, "mdc-button__label")
second_search_button.click()
time.sleep(7)

adv_searched = driver.find_element(By.CSS_SELECTOR, "#imod-view-content > div.imod-search-form.imod-field-label-align-left > div.imod-button-section > a")
adv_searched.click()
time.sleep(2)
# Search page...selects and inputs the tageted values
if search_year:
    year = driver.find_element(By.ID, 'mf_882')
    year_to_be_searched_for = Select(year)
    year_to_be_searched_for.select_by_value("string:" + str(search_year))
    time.sleep(2)
if search_state:
    state = driver.find_element(By.ID, 'mf_86')
    state_to_be_searched_for = Select(state)
    state_to_be_searched_for.select_by_value("string:" + str(search_state))
    time.sleep(2)
if search_city:
    city = driver.find_element(By.ID, 'mf_85').send_keys(search_city)
if search_major:
    major = driver.find_element(By.ID, "mf_409")
    major_to_be_searhed_for = []
    major_to_be_searhed_for = driver.find_elements(By.TAG_NAME, "OPTION")
    #major_to_be_searhed_for = Select(major)
    for major in major_to_be_searhed_for:
        m = major.get_attribute('innerHTML')
        if m == search_major:
            major.click()
            break
            
# for basic search button: search = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div[3]/div[9]/button")
#
search = driver.find_element(By.CSS_SELECTOR, "#imod-view-content > section > div.imod-search-form.imod-field-label-align-left > div.imod-button-section > button") #imod-view-content > section > div.imod-search-form.imod-field-label-align-left > div.imod-button-section > button

driver.execute_script("arguments[0].scrollIntoView();", search)
search.click()

# Profile Page...find alls the profile elements 
profilePage = driver.current_window_handle
waitfprofile = WebDriverWait(driver, 5).until(EC.presence_of_element_located((By.CLASS_NAME, "expand")))
l = [] 
profile_list = driver.find_elements(By.CLASS_NAME, "imod-directory-member-name")
num_of_alum = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div[2]/p/strong").get_attribute('innerhtml')
currenturl = driver.current_url


#loop for clicking on each profile
profile_location = 7
# range(0, len(profile_list)
x = 0
if (int(num_of_alum) < 20):
    x = x + 1        
while(x < 2):
    for profile in profile_list:
        strLocation = str(profile_location) 
        xpath = '//*[@id="imod-view-content"]/div[' + strLocation + ']/div/div/div[1]'
        profile_location = profile_location + 1
        profile = driver.find_element(By.XPATH, xpath)
        #profile.find_element(By.CLASS_NAME, "expand")
        profile.click()
        time.sleep(7)
        
        # obtains the profile info
        fname = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div/div/div[1]/div[2]/div[2]/div[2]/ul/li[1]/div[2]").get_attribute('innerHTML')
        lname = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div/div/div[1]/div[2]/div[2]/div[2]/ul/li[2]/div[2]").get_attribute('innerHTML')
        name = fname + " " + lname
        print (name)
        home_info = driver.find_element(By.XPATH, "/html/body/form/div[3]/main/section/div/div/section/div[3]/div/div/div[3]/div[2]/div[2]/div[2]/div/div/div[2]/div[1]/div/div[2]")
        driver.execute_script("arguments[0].scrollIntoView();", home_info)
        driver.execute_script("arguments[0].click();", home_info)
        email = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div/div/div[2]/div[2]/div[2]/div[2]/ul/li[1]/div[2]").get_attribute('innerHTML')
        #career_exist = exist("#imod-view-content > div > div > div:nth-child(4) > div.imod-profile-step-header > div > div.imod-profile-header-text.ng-binding.ng-scope")    
        #print(career_exist)

        headers = driver.find_elements(By.CLASS_NAME, "imod-profile-step-header")
        print(headers)
        loc = 0
        career_exist = False
        for header in headers: 
            loc = loc + 1
            h = header.get_attribute('innerText')
            print(loc)
            if h == "Career Information":
                career_exist =  not career_exist

        print(career_exist)

        # obtains employer info
        if (career_exist == True):
            info = []   
            str_cp = str(loc)                                    
            employment_info = driver.find_element(By.CSS_SELECTOR, "#imod-view-content > div > div > div:nth-child("+ str_cp +") > div.imod-profile-step-header > div > div.imod-profile-header-text.ng-binding.ng-scope")
            driver.execute_script("arguments[0].scrollIntoView();", employment_info)
            driver.execute_script("arguments[0].click();", employment_info)  
            c_info = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div/div/div[" + str_cp + "]/div[2]/div[2]/div[2]/ul").get_attribute('innerText')
            employer_info = c_info.replace("\n", " ")
            info = convert(employer_info)        
            if len(info) > 2:
                h = info[1]
                employer = h.replace('Job Title', "")
                j = info[2]
                n = j.split("Field/", 1)
                job_title = n[0]
            else:
                employer = info[1]
                job_title = "N/A"
        else:
            employer = "N/A"
            job_title = "N/A"

        print(email)
        print(employer)
        print(job_title)
        data = []
        data = name, email,job_title, employer, search_year, search_state, search_city, 

        # "w+" means the file witll be truncate, which basically means it clears the file before writing to it
        with open('tigernet_db_test.csv', 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(data)        

        driver.execute_script("window.history.go(-1)")
        time.sleep(7)
    np = 3
    if (x == 0):
        next_page = driver.find_element(By.XPATH, "//*[@id='imod-view-content']/div[27]/div/div[1]/div[" + np + "]/div/a")
        next_page.click()
        np = np + 1
    x = x + 1




# construct Outlook application instance and send intended email
    def send_email(receiver, subject, message):
        server = smtplib.SMTP('smtp-mail.outlook.com',587)
        server.ehlo()
        server.starttls()
        server.login('lance.gartrell@ourkidsreadinc.org', '****')
        email = EmailMessage()
        email['From'] = 'lance.gartrell@ourkidsreadinc.org'
        email['To'] = receiver
        email['Subject'] = subject
        email.set_content(message)
        server.send_message(email) 
        # place outside function to run: email_appeal = 'good morning ' + name + 'donate!' + 'have a good year' + name
    
    # function for adding data to excel sheet (work in progress as I dont hav office365)
    def add_to_excel(database, email, name, state, city, year):
        database.append([email, name, state, city, year])

        # dataframe Name and Age columns
        df = pd.DataFrame({'Name': [name],'Year': [year]})
        # Create a Pandas Excel writer using XlsxWriter as the engine.
        writer = pd.ExcelWriter('demodata.xlsx', engine='xlsxwriter')

        # Convert the dataframe to an XlsxWriter Excel object.
        df.to_excel(writer, sheet_name='Sheet1', index=False)

        # Close the Pandas Excel writer and output the Excel file.
        writer.close()

    def google_sheets():
        # authroizes your access to the google sheet API and drive
        scope = ['https://www.googleapis.com/auth/spreadsheets', "https://www.googleapis.com/auth/drive"]
        credentials = ServiceAccountCredentials.from_json_keyfile_name("tigernetdb.json", scope)

        # aurhorizes the specific keys for our sheet so the python machine can access it
        client = gspread.authorize(credentials) 
        gc = pygsheets.authorize(service_file='/Users/lancegartrell/Desktop/User/tigernetdb.json')

        test_sheet = gc.open_by_key("1cD7zOF-B7AUd-rxI0e_jz_gwE6Mr2BalASgkfScm8Co").sheet1
        rownum = 2

        # data frame with donor info
        df = pd.DataFrame({'a': [name], 'b': [email], 'c':[job_title], 'd': [employer]})
        test_sheet.add_rows(df.shape[0])
        gd.set_with_dataframe(test_sheet, df)
        gd.set_with_dataframe(worksheet=test_sheet,dataframe=df,include_index=False,include_column_header=False,row=test_sheet.row_count+1,resize=False)
        df_values = df.values.tolist()
        test_sheet.append_rows()
        test_sheet.values().append('Sheet1', {'valueInputOption': 'RAW'}, {'values': df_values})
        rownum += 1


states = {
    'AK': 'Alaska',
    'AL': 'Alabama',
    'AR': 'Arkansas',
    'AZ': 'Arizona',
    'CA': 'California',
    'CO': 'Colorado',
    'CT': 'Connecticut',
    'DC': 'District of Columbia',
    'DE': 'Delaware',
    'FL': 'Florida',
    'GA': 'Georgia',
    'HI': 'Hawaii',
    'IA': 'Iowa',
    'ID': 'Idaho',
    'IL': 'Illinois',
    'IN': 'Indiana',
    'KS': 'Kansas',
    'KY': 'Kentucky',
    'LA': 'Louisiana',
    'MA': 'Massachusetts',
    'MD': 'Maryland',
    'ME': 'Maine',
    'MI': 'Michigan',
    'MN': 'Minnesota',
    'MO': 'Missouri',
    'MS': 'Mississippi',
    'MT': 'Montana',
    'NC': 'North Carolina',
    'ND': 'North Dakota',
    'NE': 'Nebraska',
    'NH': 'New Hampshire',
    'NJ': 'New Jersey',
    'NM': 'New Mexico',
    'NV': 'Nevada',
    'NY': 'New York',
    'OH': 'Ohio',
    'OK': 'Oklahoma',
    'OR': 'Oregon',
    'PA': 'Pennsylvania',
    'RI': 'Rhode Island',
    'SC': 'South Carolina',
    'SD': 'South Dakota',
    'TN': 'Tennessee',
    'TX': 'Texas',
    'UT': 'Utah',
    'VA': 'Virginia',
    'VT': 'Vermont',
    'WA': 'Washington',
    'WI': 'Wisconsin',
    'WV': 'West Virginia',
    'WY': 'Wyoming'
}
