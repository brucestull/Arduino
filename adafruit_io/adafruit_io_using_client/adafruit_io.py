# ******************************************** #
#            Adafruit IO API Client            #
#   api get adafruit io requests curl client   #
#                 Version: 1.0                 #
#             Author: Bruce Stull              #
#                  2022-02-06                  #
# ******************************************** #

from Adafruit_IO import *
import pprint
import the_secrets

# Virtual environment startup:
# source C:/Users/Bruce/.virtualenvs/adafruit_io-RYTNT31i/Scripts/activate

# Resources:

# https://adafruit-io-python-client.readthedocs.io/en/latest/

# Adafruit library resource:
# https://github.com/adafruit/Adafruit_IO_Python


################ Set credentials and create Client ################
# Set Adafruit username and key:
ADAFRUIT_IO_USERNAME = the_secrets.io_username
ADAFRUIT_IO_KEY = the_secrets.io_key

# Create the client:
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)
###################################################################


################## ISSUE ##################
# It seemed that I had to set the PYTHONPATH variable again. Not sure why, yet.
# export PYTHONPATH='C:\Users\Bruce\Programming\Arduino' <= This one worked.
# $ echo $PYTHONPATH
# C:\Users\Bruce\Programming\Arduino
################ RESOLUTION ###############
# Added path_to_modules to PYTHONPATH in User Environment Variables.
###########################################


# #
# ################### Create feed and add data to feed, or add data to existing feed ###################
# # Open 'test-feed', create 'test-feed' if it doesn't exist.
# try:
#     test_feed = aio.feeds('test-feed')
#     print("Opened feed: 'test-feed'")
# except RequestError: # Doesn't exist, create a new feed
#     print("Creating feed: 'test-feed'")
#     test = Feed(name='test-feed')
#     test_feed = aio.create_feed(test)
#     print("Feed created: 'test-feed'")

# # Verified feed created on https://io.adafruit.com/FlynntKnapp/feeds/test-feed

# # Send a data point to test-feed:
# aio.send_data(test_feed.key, 91)

# # print(f"type(aio): {type(aio)}")
# # type(aio): <class 'Adafruit_IO.client.Client'>

# # Get 'data' from the feed:
# data = aio.receive(test_feed.key)

# # print(f"type(data): {type(data)}")
# # type(data): <class 'Adafruit_IO.model.Data'>

# # Print out the 'value' entry of the feed:
# print('Latest value from Test: {0}'.format(data.value))
# print(f'Latest value from Test: {data.value}')

# # Print out the whole feed and some specfic items:
# # print(f"data: {data}")
# print(f"data.created_at: {data.created_at}")
# print(f"data.updated_at: {data.updated_at}")
# print(f"data.value: {data.value}")
# ######################################################################################################


# Data(created_epoch=None, created_at='2022-02-06T14:26:32Z', updated_at='2022-02-06T14:26:32Z', value='53', completed_at=None, feed_id=1801470, expiration='1646749592.0', position=None, id='0EYGD4NPAB121QB1Y8E5ZCCW4P', lat=None, lon=None, ele=None)

# # Opened feed: 'test-feed'
# # Latest value from Test: 91
# # Latest value from Test: 91
# ######### Time zone difference #########
# # Hour:
# # 14 - 9 = 5
# # 9 - 14 = -5
# ########################################
# # data.created_at: 2022-02-06T14:36:17Z
# # data.updated_at: 2022-02-06T14:36:17Z
# # data.value: 91


# #
##################### Get feed 'value's #####################
############ Using feed_key ############
feed_key = 'temperatureesp32'
########################################

# Get an array of all data from feed 'feed_key'
data = aio.data(feed_key)

# print(f"type(data): {type(data)}")
# # type(data): <class 'list'>
# print(f"type(data[0]): {type(data[0])}")
# # type(data[0]): <class 'Adafruit_IO.model.Data'>
# print(f"type(data[0][0]): {type(data[0][0])}")
# # type(data[0][0]): <class 'int'>

# print(data)
# # This is a large set of data.
# print(len(data))
# # 1000

# Print two data points' elements'.
print(data[0])
print(data[1])
Data(created_epoch=1644239448, created_at='2022-02-07T13:10:48Z', updated_at=None, value='65.55', completed_at=None, feed_id=1767913, expiration='2022-03-09T13:10:48Z', position=None, id='0EYH5HAA90AN18ZRJ6EF0VZ08P', lat='0.0', lon='0.0', ele='0.0')
Data(created_epoch=1644239382, created_at='2022-02-07T13:09:42Z', updated_at=None, value='65.62', completed_at=None, feed_id=1767913, expiration='2022-03-09T13:09:42Z', position=None, id='0EYH5GP0YD293T4NV0N5XW5T07', lat='0.0', lon='0.0', ele='0.0')

# # Print out all the results.
# for d in data:
#     print('Data value: {0}'.format(d.value))
#############################################################
