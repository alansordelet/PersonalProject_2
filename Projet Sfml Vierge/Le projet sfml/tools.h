#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"


using namespace sf;
using namespace std;

namespace tools
{

	int iRand(int _min, int _max);

	double frand(float _min, float _max);

	void restartClock();

	float GetTimeDelta();

	float lerp(float v0, float v1, float t);

	Vector2f vec2f_lerp(Vector2f v0, Vector2f v1, float t);

	Vector3f vec3f_lerp(Vector3f v0, Vector3f v1, float t);

	Color color_lerp(Color v0, Color v1, float t);

	bool Circle_Collision(Vector2f _pos1, Vector2f _pos2, float _rayon1, float _rayon2);

	bool Rectangle_Collision(FloatRect _box1, FloatRect _box2);

	float distance(sf::Vector2f _vector1, sf::Vector2f _vector2);

	sf::Vector2f normalize(sf::Vector2f _vecteur);

	float map(float _distance, float _debutRayon, float _finRayon, float _minVitesse, float _maxVitesse);

	float dot(sf::Vector2f _vector1, sf::Vector2f _vector2);

	float angleBetween(sf::Vector2f _vector1, sf::Vector2f _vector2);

	float magnitude(sf::Vector2f _vector);

	void subtract2Vector(sf::Vector2f& _vector1, sf::Vector2f _vector2);

	void multiple2Vector(sf::Vector2f& _vector1, sf::Vector2f _vector2);

	void multipleVectorFloat(sf::Vector2f& _vector1, float _float);

	void ajout2Vector(sf::Vector2f& _vector1, sf::Vector2f _vector2);

	void divisionVectorFloat(sf::Vector2f& _vector, float _float);

	sf::Vector2f scalaireProjection(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);

	void limitVectorFloat(sf::Vector2f& _vector, float _float);

};





