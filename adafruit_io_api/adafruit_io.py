# ********************************************** #
#                Adafruit IO API                 #
#   api get adafruit io requests response curl   #
#                  Version: 1.0                  #
#              Author: Bruce Stull               #
#                   2022-02-05                   #
# ********************************************** #

import requests
import pprint

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


# Using 'curl':
# curl -H "X-AIO-Key: {io_key}" /{username}/feeds/{feed_key}

# response = requests.get('https://api.ipify.org')
# print(response.url)
# print(response.text)
# print(response.status_code)
# print(response.encoding)
# print(response.headers)


# response = requests.get('https://api.ipify.org', params={'format': 'json'})
# print(response.url) # https://api.ipify.org/?format=json


# curl "https://io.adafruit.com/api/v2/user_name/feeds?x-aio-key=io_key"

username = ''
io_key = ''

response = requests.get(f"https://io.adafruit.com/api/v2/{username}/feeds", params={'x-aio-key': io_key})

print(response.url)
print(response.status_code)
print(response.encoding)
print(response.headers)
# print(response.text)

data = response.json()
pprint.pprint(data)
