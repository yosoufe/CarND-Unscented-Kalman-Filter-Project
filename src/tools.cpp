#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {
	//reset the files and destroy the contents
	myfile = std::fopen("NIS_lidar","w");
	std::fclose(myfile);
	myfile = std::fopen("NIS_radar","w");
	std::fclose(myfile);

	gp_ = popen("gnuplot -persist" , "w");
}

void Tools::updateGraph(double value,graphType ty){
	switch(ty){
		case LASER:
			myfile = std::fopen("NIS_lidar","a");
			break;
		case RADAR:
			myfile = std::fopen("NIS_radar","a");
			break;
	}
	if(myfile != NULL){
		std::string toWrite = std::to_string(value) + '\n';
		std::fwrite(toWrite.c_str(),1,toWrite.length(),myfile);
		std::fclose(myfile);
	}

	if (gp_!=NULL){
		fprintf(gp_ , "call '../plotScript.gp'\n");
		std::fflush(gp_);
	}
}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const std::vector<VectorXd> &estimations,
															const std::vector<VectorXd> &ground_truth) {
	VectorXd rmse(4);
	rmse << 0,0,0,0;

	if (estimations.size()!=ground_truth.size() || estimations.size()==0){
		std::cout << "invalid data to calculate the RMSE" << std::endl;
		return rmse;
	}

	//accumulate squared residuals
	for(int i=0; i < estimations.size(); i++){
		VectorXd residual = estimations[i] - ground_truth[i];
		residual = residual.array() * residual.array();
		rmse += residual;
	}
	rmse = rmse / estimations.size();
	rmse = rmse.array().sqrt();
	return rmse;

}
