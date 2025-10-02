import os
from roboflow import Roboflow

rf = Roboflow(api_key=os.environ["ROBOFLOW_API_KEY"])
project = rf.workspace("roboflow-100").project("hard-hat-workers")  # cambia si usas otro dataset
dataset = project.version(1).download("yolov8")  # revisa la versión disponible