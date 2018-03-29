#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	this->color_1 = ofColor(239);
	this->color_2 = ofColor(139, 39, 39);

	ofBackground(this->color_1);
	ofSetLineWidth(5);
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 200;
	int x_step = 1;

	ofFill();
	ofSetColor(this->color_2);
	ofBeginShape();
	for (int deg = 0; deg < 360; deg++) {

		ofVertex(radius * cos(deg * DEG_TO_RAD) + ofGetWidth() / 2, radius * sin(deg * DEG_TO_RAD) + ofGetHeight() / 2);
	}
	ofEndShape(true);

	ofNoFill();
	for (int i = 0; i < 10; i++) {

		vector<ofPoint> vertices;
		bool overlap = false;
		float r_1 = ofRandom(0.0003, 0.001);
		float r_2 = ofRandom(0.0005, 0.002);
		for (int x = 0; x < ofGetWidth(); x += x_step) {

			ofPoint point = ofPoint(x, ofMap(ofNoise(i, x * r_1, ofGetFrameNum() * r_2), 0, 1, -ofGetHeight() * 0.2, ofGetHeight() * 1.2));
			if (point.distance(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2)) < radius) {

				if (overlap) {

					vertices.push_back(point);
				}
				else {

					ofSetColor(color_2);
					ofBeginShape();
					ofVertices(vertices);
					ofEndShape();

					overlap = true;
					vertices.clear();
				}
			}
			else {

				if (overlap) {

					ofSetColor(color_1);
					ofBeginShape();
					ofVertices(vertices);
					ofEndShape();

					overlap = false;
					vertices.clear();
				}
				else {

					vertices.push_back(point);
				}
			}
		}

		ofSetColor(color_2);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}