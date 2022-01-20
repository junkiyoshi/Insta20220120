#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	this->draw_line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	auto ico_sphere = ofIcoSpherePrimitive(150, 3);
	auto triangles = ico_sphere.getMesh().getUniqueFaces();
	for (auto& triangle : triangles) {

		auto avg = glm::vec3(triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		this->line.addVertex(avg);
	}

	for (int i = 0; i < this->line.getNumVertices(); i++) {

		for (int k = i + 1; k < this->line.getNumVertices(); k++) {

			auto& location = this->line.getVertex(i);
			auto& other = this->line.getVertex(k);

			if (glm::distance(location, other) < 15) {

				this->line.addIndex(i);
				this->line.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_line = this->line;

	for (auto& vertex : this->draw_line.getVertices()) {

		auto noise_value = ofNoise(glm::vec4(vertex * 0.0015, ofGetFrameNum() * 0.01));

		if (noise_value > 0.5 && noise_value < 0.55) {

			vertex = glm::normalize(vertex) * ofMap(noise_value, 0.5, 0.55, 200, 300);
		}
		else if (noise_value > 0.55) {

			vertex = glm::normalize(vertex) * 300;
		}
		else {

			vertex = glm::normalize(vertex) * 200;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	ofTranslate(-320, 0, 0);

	this->draw_line.drawWireframe();

	ofTranslate(640, 0, 0);

	for (auto& vertex : this->draw_line.getVertices()) {

		ofDrawSphere(vertex, 3.5);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}