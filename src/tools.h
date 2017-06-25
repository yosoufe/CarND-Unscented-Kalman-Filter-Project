#ifndef TOOLS_H_
#define TOOLS_H_
#include <vector>
#include "Eigen/Dense"
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;
//using namespace std;

class Tools {
public:	

	FILE *gp_;
	enum graphType{
		LASER,
		RADAR
	};


	FILE *myfile;
  /**
  * Constructor.
  */
	Tools();

  /**
  * Destructor.
  */
  virtual ~Tools();

  /**
  * A helper method to calculate RMSE.
  */
	VectorXd CalculateRMSE(const std::vector<VectorXd> &estimations, const std::vector<VectorXd> &ground_truth);
	void updateGraph(double value,graphType ty);

};

#endif /* TOOLS_H_ */
