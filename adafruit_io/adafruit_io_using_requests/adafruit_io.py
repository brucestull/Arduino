# ********************************************** #
#                Adafruit IO API                 #
#   api get adafruit io requests response curl   #
#                  Version: 1.0                  #
#              Author: Bruce Stull               #
#                   2022-02-05                   #
# ********************************************** #


import requests
import pprint
import the_secrets

# Virtual environment startup:
# source C:/Users/Bruce/.virtualenvs/adafruit_io-RYTNT31i/Scripts/activate


################## ISSUE ##################
# It seemed that I had to set the PYTHONPATH variable again. Not sure why, yet.
# export PYTHONPATH='C:\Users\Bruce\Programming\Arduino' <= This one worked.
# $ echo $PYTHONPATH
# C:\Users\Bruce\Programming\Arduino
################ RESOLUTION ###############
# Added path_to_modules to PYTHONPATH in User Environment Variables.
###########################################




# Resources:

# Link to feeds:
# https://io.adafruit.com/FlynntKnapp/feeds

# Link to feed:
# https://io.adafruit.com/FlynntKnapp/feeds/humidityesp32

# API Documentation:
# https://io.adafruit.com/api/docs/#adafruit-io-http-api

# API link for feeds:
# https://io.adafruit.com/api/v2/{username}/feeds

# PDX requests
# https://github.com/PdxCodeGuild/class_otter/blob/main/1%20Python/docs/15%20Requests.md


username = the_secrets.io_username
io_key = the_secrets.io_key


############# List of all feeds #############
# feeds_response.py
response = requests.get(f"https://io.adafruit.com/api/v2/{username}/feeds", params={'x-aio-key': io_key})

# print(response.headers)

data = response.json()
# pprint.pprint(data)

print(f"Headers date: {response.headers['date']}")

for data_point in data:
  print(data_point['key'])
  print(data_point['description'])
  print(data_point['last_value'])
  print(data_point['id'])
  print(data_point['updated_at'])
#############################################


############ Using feed_key ############
feed_key = 'temperatureesp32'
### List of keys ###
# temperatureesp8266
# humidityesp8266
# humidityesp32
# temperatureesp32
# batteryvoltageesp32
# toggle-led
########################################


# ############################ Specific feed ############################
# # feed_response.py
# # Seems to return the latest value and general feed information.
# response = requests.get(f"https://io.adafruit.com/api/v2/{username}/feeds/{feed_key}", params={'x-aio-key': io_key})

# data = response.json()
# pprint.pprint(data)

# print(f"Headers date: {response.headers['date']}")
# pprint.pprint(f"Feed name: {data['name']}")
# pprint.pprint(f"Feed updated at: {data['updated_at']}")
# pprint.pprint(f"Feed last value: {data['last_value']}")
# #######################################################################


# ##################### Details of a feed #####################
# # feed_response_details.py
# response = requests.get(f"https://io.adafruit.com/api/v2/{username}/feeds/{feed_key}/details", params={'x-aio-key': io_key})

# data = response.json()
# pprint.pprint(data)

# pprint.pprint(data['details']['data']['last'])
# #############################################################


# ##################### Request last 5 data points #####################
# # feed_response_limit_5.py
# response = requests.get(f"https://io.adafruit.com/api/v2/{username}/feeds/{feed_key}/data?limit=5", params={'x-aio-key': io_key})

# data = response.json()
# pprint.pprint(data)

# print(f"Headers date: {response.headers['date']}")

# print(data[0]['feed_key'])
# for data_point in data:
#     print(f"{data_point['created_at']}: {data_point['value']}")
# ######################################################################

