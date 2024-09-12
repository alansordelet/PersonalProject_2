#include "tools.h"

sf::Clock sfclock;
sf::Time sfTime;

namespace tools
{
	int iRand(int _min, int _max)
	{ 
		srand(NULL);
		return rand() % (_max - _min) + _min;
	}

	double frand(float _min, float _max)
	{
		return ((rand() / (double)RAND_MAX) * ((double)_max - (double)_min) + (double)_min);
	}

	void restartClock()
	{
		sfTime = sfclock.restart();
	}

	float GetTimeDelta()
	{
		return sfTime.asSeconds();
	}

	float lerp(float v0, float v1, float t)
	{
		return (1 - t) * v0 + t * v1;
	}


	Vector2f vec2f_lerp(Vector2f v0, Vector2f v1, float t)
	{
		Vector2f tmp;
		tmp.x = (1 - t) * v0.x + t * v1.x;
		tmp.y = (1 - t) * v0.y + t * v1.y;
		return tmp;
	}


	Vector3f vec3f_lerp(Vector3f v0, Vector3f v1, float t)
	{
		Vector3f tmp;
		tmp.x = (1 - t) * v0.x + t * v1.x;
		tmp.y = (1 - t) * v0.y + t * v1.y;
		tmp.z = (1 - t) * v0.z + t * v1.z;
		return tmp;
	}


	Color color_lerp(Color v0, Color v1, float t)
	{
		Color tmp;
		tmp.r = (1 - t) * v0.r + t * v1.r;
		tmp.g = (1 - t) * v0.g + t * v1.g;
		tmp.b = (1 - t) * v0.b + t * v1.b;
		tmp.a = (1 - t) * v0.a + t * v1.a;
		return tmp;
	}

	bool Circle_Collision(Vector2f _pos1, Vector2f _pos2, float _rayon1, float _rayon2)
	{
		// if (sqrt(pow(_pos1.x - _pos2.x, 2) + pow(_pos1.y - _pos2.y, 2)) < _rayon1 + _rayon2) // Version non optimisé
		// Version Optimisé
		if ((_pos1.x - _pos2.x) * (_pos1.x - _pos2.x) + (_pos1.y - _pos2.y) * (_pos1.y - _pos2.y) < (_rayon1 + _rayon2) * (_rayon1 + _rayon2))
		{
			return true;
		}
		else return false;
	}

	bool Rectangle_Collision(FloatRect _box1, FloatRect _box2)
	{
		if ((_box2.left >= _box1.left + _box1.width)      // trop à droite
			|| (_box2.left + _box2.width <= _box1.left) // trop à gauche
			|| (_box2.top >= _box1.top + _box1.height) // trop en bas
			|| (_box2.top + _box2.height <= _box1.top))  // trop en haut
			return false;
		else
			return true;
	}

	float distance(sf::Vector2f _vector1, sf::Vector2f _vector2) {
		return std::sqrt(std::pow((_vector2.x - _vector1.x), 2) + std::pow((_vector2.y - _vector1.y), 2));
	}
	sf::Vector2f normalize(sf::Vector2f _vecteur) {
		float tmp = std::sqrt((std::pow(_vecteur.x, 2) + (std::pow(_vecteur.y, 2))));

		_vecteur.x /= tmp;
		_vecteur.y /= tmp;

		return _vecteur;
	}
	float map(float _distance, float _debutRayon, float _finRayon, float _minVitesse, float _maxVitesse) {
		if (_distance >= _debutRayon && _distance <= _finRayon)
			return (_maxVitesse / (_finRayon / _distance)) + _minVitesse;
	}
	float dot(sf::Vector2f _vector1, sf::Vector2f _vector2) {
		return (_vector1.x * _vector2.x) + (_vector1.y * _vector2.y);
	}
	float angleBetween(sf::Vector2f _vector1, sf::Vector2f _vector2) {
		float tmp = std::acos(dot(_vector1, _vector2) / (magnitude(_vector1) * magnitude(_vector2)));
		return tmp * (180 / 3.14f);
	}
	float magnitude(sf::Vector2f _vector) {
		return std::sqrt((std::pow(_vector.x, 2) + (std::pow(_vector.y, 2))));
	}
	void subtract2Vector(sf::Vector2f& _vector1, sf::Vector2f _vector2) {
		_vector1.x -= _vector2.x;
		_vector1.y -= _vector2.y;
	}
	void multiple2Vector(sf::Vector2f& _vector1, sf::Vector2f _vector2) {
		_vector1.x *= _vector2.x;
		_vector1.y *= _vector2.y;
	}
	void multipleVectorFloat(sf::Vector2f& _vector1, float _float) {
		_vector1.x *= _float;
		_vector1.y *= _float;
	}
	void ajout2Vector(sf::Vector2f& _vector1, sf::Vector2f _vector2) {
		_vector1.x += _vector2.x;
		_vector1.y += _vector2.y;
	}
	void divisionVectorFloat(sf::Vector2f& _vector, float _float) {
		_vector.x /= _float;
		_vector.y /= _float;
	}
	sf::Vector2f scalaireProjection(sf::Vector2f pos, sf::Vector2f a, sf::Vector2f b) {
		subtract2Vector(pos, a);
		subtract2Vector(b, a);
		sf::Vector2f v1 = pos;
		sf::Vector2f v2 = b;

		v2 = normalize(v2);
		float tmp = dot(v1, v2);
		tools::multipleVectorFloat(v2, tmp);
		tools::ajout2Vector(v2, a);

		return v2;
	}
	void limitVectorFloat(sf::Vector2f& _vector, float _float) {
		if (_vector.x > _float)
			_vector.x = _float;
		else if (_vector.x < -_float)
			_vector.x = -_float;
		if (_vector.y > _float)
			_vector.y = _float;
		else if (_vector.y < -_float)
			_vector.y = -_float;
	}
};