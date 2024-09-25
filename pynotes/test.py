import math
import argparse
import os
import shutil

path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
path = os.path.join(path, "test")
if not os.path.exists(path):
    os.makedirs(path)