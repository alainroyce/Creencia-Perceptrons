#include<iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <vector>

using namespace std;
struct Data {
public:


	Data(	
		vector<int> datas
	)
	{	
		surveydatas = datas;
	}
	
	vector<int> surveydatas;
};


int main()
{

#pragma region Parser
	ifstream inputFile;
	inputFile.open("C:\\Users\\alain\\Downloads\\Datasheet.csv");
	vector<Data> dataset;
	string line = "";

	//getline(inputFile, line);
	//line = "";
	while (getline(inputFile, line)) {

	
		vector<int> datas;

		string tempString = "";

		stringstream inputString(line);


		for (int i = 0; i < 42; i++)
		{
			getline(inputString, tempString, ',');
			datas.push_back(atoi(tempString.c_str()));
		}
		

		Data Dataset(datas);
		dataset.push_back(Dataset);

		line = "";
	}


#pragma endregion Parser
	
	
	
	float r;
	vector<float> weights;

	for (int i = 0; i < 42; i++)
	{
		r = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2)));
		//r = -1 + (rand() % 2);
		//cout << r << endl;
		weights.push_back(r);
		//weights.push_back(1);
	}
	weights.push_back(1);

	//cout << dataset.size();
#pragma region Training
	int MaxIterations;
	float LearningRate;
	int FeatureCount = 41;
	int SampleCount = dataset.size() - 1;
	float percentage;
	int TrainSamples;
	int TestSamples;

	cout << "Enter the number of iterations" << endl;
	cin >> MaxIterations;
	cout << "Learning Rate: " << endl;
	cin >> LearningRate;
	cout << "Enter the percentage of data you want for training: " << endl;
	cin >> percentage;
	TrainSamples = dataset.size() * (percentage / 100);
	TestSamples = dataset.size() - TrainSamples;
	//cout <<"Train Sample Count: " << TrainSamples << endl;
	//cout << "Test Sample Count: " << TestSamples << endl;


	
	vector<Data> datasetCopy = dataset;
	vector<Data> trainingData;
	vector<Data> testingData;

	for (int i = 0; i < TrainSamples; i++)
	{
		int index = rand() % (dataset.size() - 1);
		
		trainingData.push_back(datasetCopy[index]);
		dataset.erase(dataset.begin() + index);
	
	}
	for (int i = 0; i < 10; i++)
	{
		int index = rand() % (dataset.size() - 1);
		cout << "index: " << index << endl;
	}
	//cout << "Data size before entering: " << dataset.size() << endl;

	//cout << "TrainingData Size: " << trainingData.size() << " Dataset Size: " << dataset.size() << endl;

	for (int i = 0; i < MaxIterations; i++)
	{
		int index = 0 + (rand() % TrainSamples);
		
		float activation = 0;
		int output;
		//cout << i << " Iteration: " << MaxIterations << " Index: " << index << endl;

		for (int j = 0; j < FeatureCount; j++)
		{
			activation += trainingData[index].surveydatas[j] * weights[j] ;
			
		}
		activation += 1 * weights[42];
		if (activation > 0)
		{
			output = 1;
		}
		else if (activation <= 0)
		{
			output = 0;
		}

		int error = trainingData[index].surveydatas[41] - output;

		cout << " Error: " << error << endl;
		for (int j = 0; j < FeatureCount; j++)
		{
			weights[j] += LearningRate * error * trainingData[index].surveydatas[j];
		}
		weights[42] += LearningRate * error * 1;
	}
#pragma endregion Training

	/// ///////////////////////////////////////////////////////////
	
	for (int i = 0; i < dataset.size(); i++)
	{
		testingData.push_back(dataset[i]);
		//dataset.erase(dataset.begin() + i);
	}
	////////////////////////////////////////////////////////////////////////////
#pragma region Testing

	int correct=0 ; int incorrect=0;
	int TruePositive = 0; int FalsePositive = 0;
	int TrueNegative = 0; int FalseNegative = 0;
	int PredictedRisktakers = 0; int ActualRisktakers = 0;
	int ActualNonRisktakers = 0; int PredictedNonRisktakers = 0;

	cout << "Testing Data size before entering: " << testingData.size();
	for (int i = 0; i < testingData.size(); i++)
	{
		float activation = 0;
		int output;

		
		for (int j = 0; j < FeatureCount; j++)
		{
			activation += testingData[i].surveydatas[j] *weights[j];
		}
		activation +=  1 * weights[42];
		if (activation > 0)
		{
			PredictedRisktakers++;
			output = 1;
			
		}
		else if (activation <= 0)
		{
			output = 0;
			PredictedNonRisktakers++;
		}

		if (testingData[i].surveydatas[41] == 1)\
		{
			ActualRisktakers++;
		}
		else
		{
			ActualNonRisktakers++;
		}
		

		if (output == testingData[i].surveydatas[41])
		{
			correct++;
			if (output == 1)
			{
				TruePositive++;
			}
			else
			{
				TrueNegative++;
			}
		}
		else
		{
			incorrect++;
			if (output == 1)
			{
				FalsePositive++;
			}
			else
			{
				FalseNegative++;
			}
		}
	cout << "Output: " << output << endl;
	
	float accuracy = 100 * correct / (correct + incorrect);

	

	if (i == testingData.size()-1)
	{
		cout << "Accuracy: " << accuracy <<"%"<< endl;
		cout << "Correct: " << correct << " Incorrect: " << incorrect << endl;
		cout << "TruePositive: " << TruePositive << " FalsePositive: " << FalsePositive << endl;
		cout << "TrueNegative: " << TrueNegative << " FalseNegative: " << FalseNegative << endl;
		cout << "ActualRiskTakers: " << ActualRisktakers << " PredictedRiskTakers: " << PredictedRisktakers << endl;
		cout << "ActualNonRiskTakers: " << ActualNonRisktakers << " PredictedNonRiskTakers: " << PredictedNonRisktakers << endl;
	}

	}

#pragma endregion Testing

	return 0;
}