# -*- coding: utf-8 -*-
"""
Created on Thu Jan 25 19:20:45 2018

@author: Patrick Deubel
"""
from numpy import *
import numpy as np
import h5py

#Open .npy file
new_data = load(open("bvlc_alexnet.npy", "rb"), encoding = "latin1").item()

convertedH5= h5py.File('AlexNet_Weights_Transposed.h5', 'w')

#use naming convention for each group
g1 = convertedH5.create_group('conv_1')

dataset = new_data["conv1"][0]
dataset = np.transpose(dataset, (3, 2, 1, 0))

g1.create_dataset('conv_1_W', data=dataset)
g1.create_dataset('conv_1_b', data=new_data["conv1"][1])

g2 = convertedH5.create_group('conv_2')

dataset = new_data["conv2"][0]
dataset = np.transpose(dataset, (3, 2, 1, 0))

g2.create_dataset('conv_2_W', data=dataset)
g2.create_dataset('conv_2_b', data=new_data["conv2"][1])

g3 = convertedH5.create_group('conv_3')

dataset = new_data["conv3"][0]
dataset = np.transpose(dataset, (3, 2, 1, 0))

g3.create_dataset('conv_3_W', data=dataset)
g3.create_dataset('conv_3_b', data=new_data["conv3"][1])

g4 = convertedH5.create_group('conv_4')

dataset = new_data["conv4"][0]
dataset = np.transpose(dataset, (3, 2, 1, 0))

g4.create_dataset('conv_4_W', data=dataset)
g4.create_dataset('conv_4_b', data=new_data["conv4"][1])

g5 = convertedH5.create_group('conv_5')

dataset = new_data["conv5"][0]
dataset = np.transpose(dataset, (3, 2, 1, 0))

g5.create_dataset('conv_5_W', data=dataset)
g5.create_dataset('conv_5_b', data=new_data["conv5"][1])

g6 = convertedH5.create_group('dense_1')

dataset = new_data["fc6"][0]
dataset = np.transpose(dataset, (1, 0))

g6.create_dataset('dense_1_W', data=dataset)
g6.create_dataset('dense_1_b', data=new_data["fc6"][1])

g7 = convertedH5.create_group('dense_2')

dataset = new_data["fc7"][0]
dataset = np.transpose(dataset, (1, 0))

g7.create_dataset('dense_2_W', data=dataset)
g7.create_dataset('dense_2_b', data=new_data["fc7"][1])

g8 = convertedH5.create_group('dense_3')

dataset = new_data["fc8"][0]
dataset = np.transpose(dataset, (1, 0))

g8.create_dataset('dense_3_W', data=dataset)
g8.create_dataset('dense_3_b', data=new_data["fc8"][1])


convertedH5.close()

