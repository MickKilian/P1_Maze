#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>

class	Dijkstra {
	public:
		Dijkstra();
		Dijkstra(int, int, int, int, int, int);
		~Dijkstra();
		int		getId();
		int		getStatus();
		int		getF();
		int		getG();
		int		getH();
		int		getPreviousNode();
		void	setId(int id);
		void	setStatus(int status);
		void	setF(int value);
		void	setG(int value);
		void	setH(int value);
		void	setPreviousNode(int id);

	private:
		int		_id;
		int		_status;
		int		_f;
		int		_g;
		int		_h;
		int		_previousNode;
};

#endif // DIJKSTRA_H
