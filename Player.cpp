#include "Player.hpp"

Player::Player() : _id(-1), _type(-1), _position(Point(-1, -1)), _orientation(0),
	_nbcoins(0), _lives(0), _movingSpeedRate(1), _maxSpeed(1), _strategy(1),
	_sizeX(0), _sizeY(0), _dimInc(0), _forceForward(0), _tolerance(0), _action(),
	_moving(false), _indexInPath(0) {
}

Player::Player(int id, int type, Point position, double orientation,
	int nbcoins, int lives, int movingSpeedRate, int maxSpeed, int strategy,
	int startingCell, int sizeX, int sizeY, double dimInc, bool forceForward,
	double tolerance, bool moving, unsigned index) :
	_id(id), _type(type), _position(position), _orientation(orientation),
	_nbcoins(nbcoins), _lives(lives), _movingSpeedRate(movingSpeedRate), _maxSpeed(maxSpeed),
	_strategy(strategy), _startingCell(startingCell), _sizeX(sizeX), _sizeY (sizeY), _dimInc(dimInc),
	_forceForward(forceForward), _tolerance(tolerance), _moving(moving), _indexInPath(index) {
		_action = Action(position, orientation, Point(0, 0), maxSpeed, forceForward, tolerance);
}

Player::~Player() {
}

int	Player::getId() {
	return (_id);
}

int	Player::getType() {
	return (_type);
}

Point	Player::getPosition() {
	return (_position);
}

double	Player::getOrientation() {
	return (_orientation);
}

int	Player::getNbCoins() {
	return (_nbcoins);
}

int	Player::getLives() {
	return (_lives);
}

int	Player::getMovingSpeedRate() {
	return (_movingSpeedRate);
}

int	Player::getMaxSpeed() {
	return (_maxSpeed);
}

int	Player::getStrategy() {
	return (_strategy);
}

int	Player::getStartingCell() {
	return (_startingCell);
}

int	Player::getSizeX() {
	return (_sizeX);
}

int	Player::getSizeY() {
	return (_sizeY);
}

Route	Player::getRoute() {
	return (_route);
}

Path	Player::getPath() {
	return (_path);
}

double	Player::getDimInc() {
	return (_dimInc);
}

bool	Player::getForceForward() {
	return (_forceForward);
}

double	Player::getTolerance() {
	return (_tolerance);
}

Action	Player::getAction() {
	return (_action);
}

bool	Player::getMoving() {
	return (_moving);
}

Movement	Player::getMovement() {
	return (_movement);
}

unsigned	Player::getIndexInPath() {
	return (_indexInPath);
}

void	Player::setId(int id) {
	_id = id;
}

void	Player::setType(int type) {
	_type = type;
}

void	Player::setPosition(Point point) {
	_position = point;
}

void	Player::setOrientation(double orientation) {
	_orientation = orientation;
}

void	Player::setNbCoins(int nbcoins) {
	_nbcoins = nbcoins;
}

void	Player::setLives(int lives) {
	_lives =lives;
}

void	Player::setMovingSpeedRate(int speed) {
	_movingSpeedRate = speed;
}

void	Player::setMaxSpeed(int maxSpeed) {
	_maxSpeed = maxSpeed;
}

void	Player::setStartingCell(int id) {
	_startingCell = id;
}

void	Player::setStrategy(int strategy) {
	_strategy = strategy;
}

void	Player::setRoute(Route route) {
	_route = route;
}

void	Player::setPath(Path path) {
	_path = path;
}

void	Player::setDimInc(double value) {
	_dimInc = value;
}

void	Player::setAction(Action action) {
	_action = action;
}

void	Player::setMoving(bool moving) {
	_moving = moving;
}

void	Player::setMovement(Movement movement) {
	_movement = movement;
}

void	Player::setIndexInPath(unsigned index) {
	_indexInPath = index;
}

Path	Player::calcPath(Route route, int interp) {
	//computes a path along the specified route depending on the specified timestep_inc inc and the type of interpolation (0: STRAIGHT)
	Path	path;
	double	d;		//variable used to hold distances
	double	x_inc;	//variable used to hold cumulated distances
	double	y_inc;	//variable used to hold cumulated distances

	//route.display();
	// run for loop from beginning to end of route
	for (unsigned i = 0; i < route.getCell().size() - 1; ++i) {
		if (interp == 0) {
			d = Utils::dist(	Utils::cellIdToPoint(route.getCell()[i], _sizeX),
								Utils::cellIdToPoint(route.getCell()[i + 1], _sizeX));
			x_inc = (Utils::cellIdToX(route.getCell()[i + 1], _sizeX) - Utils::cellIdToX(route.getCell()[i], _sizeX)) * _dimInc / d;
			y_inc = (Utils::cellIdToY(route.getCell()[i + 1], _sizeX) - Utils::cellIdToY(route.getCell()[i], _sizeX)) * _dimInc / d;
			for (int j = 0; j * _dimInc < d; ++j) {
				path.addPoint(Point(	Utils::cellIdToX(route.getCell()[i], _sizeX) + j * x_inc,
										Utils::cellIdToY(route.getCell()[i], _sizeX) + j * y_inc));
			}
		}
	}
	path.addPoint(Point(	Utils::cellIdToX(*(route.getCell().end() - 1), _sizeX),
							Utils::cellIdToY(*(route.getCell().end() - 1), _sizeX)));
	return (path);
}

void	Player::printStatus() {
	std::cout << "Player : " << _id << std::endl;
	std::cout << "   type : " << _type << std::endl;
	std::cout << "   position : ";
	_position.display();
	std::cout << std::endl;
	std::cout << "   orientation : " << _orientation << std::endl;
	std::cout << "   speed: (" << _movingSpeedRate << ", " << _maxSpeed << ")" << std::endl;
	std::cout << std::endl;
}

void	Player::move() {
	if (_indexInPath < _path.getPoint().size() - 1) {
		if (!Utils::samePoints(_position, _path.getPoint()[_indexInPath], _tolerance)) {
			_position.display();
			std::cout << std::endl;
			_path.getPoint()[_indexInPath].display();
			std::cout << std::endl;
			std::cout << "Warning : player position is not maching current path position" << std::endl;
		}
		else {
			setMoving(true);
			_action.decision(_path.getPoint()[_indexInPath + 1]);
			updateOrientPosition(_path.getPoint()[_indexInPath + 1], _action.getNewOrientation());
		}
	}
	else
	{
		setMoving(false);
		//std::cout << "Path is complete" << std::endl;
	}
/*	for (unsigned i = 0; i < _path.getPoint().size(); ++i) {
		std::cout << i << " : ";
		_path.getPoint()[i].display();
		std::cout << " ";
		_action.decision(_path.getPoint()[i]);
		_action.display();
		std::cout << std::endl;
		updateOrientPosition(_path.getPoint()[i], _action.getNewOrientation());
	}
*/
}

void	Player::updateOrientPosition(Point point, double angle) {
	setPosition(point);
	setOrientation(angle);
	setIndexInPath(getIndexInPath() + 1);
	updateAction();
}

void	Player::updateAction() {
	_action.setPosition(_position);
	_action.setOrientation(_orientation);
}
