#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
from rosclarifai.msg import TagList
from maelstrom.msg import TagList
from clarifai.client import ClarifaiApi
import os
class Classifier():
	def __init__(self):
		os.environ['CLARIFAI_APP_ID']='QCk5pf9LmMXVxQ5bElovZaIl79kKlb8KcwDZzsmR'
		os.environ['CLARIFAI_APP_SECRET']='5iN32kJkOm-3ajqLmWxJuGLa8BzuoxMqTwOidYM3'
		self.cfa = ClarifaiApi()

	def tag(self, data):
		result 	= self.cfa.tag_images(data)['results'][0]['result']['tag']['classes']
		return result


class Main():
	def __init__(self):
		rospy.init_node('main', anonymous=False)
		rospy.on_shutdown(self.shutdown)
		self.classifier = Classifier()
		rospy.Subscriber("/camera/rgb/image_rect_color", Image, self.sensorInput)
		self.publisher = rospy.Publisher('results', TagList, queue_size=10)

	def sensorInput(self, img):
		cv2.imwrite('li.jpg', CvBridge().imgmsg_to_cv2(img, 'bgr8'))
		self.results = self.classifier.tag(open('li.jpg'))
		resultMsg = TagList()
		resultMsg.tags  = self.results
		self.publisher.publish(resultMsg)

	def shutdown(self):
		rospy.loginfo("stopping")

if __name__ == "__main__":
	while not rospy.is_shutdown():
		Main()
		rospy.spin()
