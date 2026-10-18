#include <iostream>
#include<cstdlib>
using namespace std;
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuiestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int CorrectAnser = 0;
	int PlayerAnser = 0;
	bool AnswerResult = false;

};
struct stQuizz
{
	stQuiestion QuestionList[100];
	int NumberOfQuestions;
	enQuestionLevel QuestionsLevel;
	enOperationType OperationType;
	int NumberOfRightQuestions;
	int NumberOfWrongQuestions;
	bool IsPass = false;

};
int RandomNumber(int From, int To)
{
	short randNumber = rand() % (To - From + 1) + From;
	return randNumber;

}
int ReadHowManyQuestion()
{
	int Questions;
	cout << "Enter how many questions do you want to answer ? ";
	cin >> Questions;
	return Questions;
}
enQuestionLevel ReadQuestionLevel()
{
	int Number;
	cout << "\nEnter Questions Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
	cin >> Number;
	return enQuestionLevel(Number);

}
enOperationType ReadOperationType()
{

	int Type;
	cout << "\nEnter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix  ? ";
	cin >> Type;
	return enOperationType(Type);
}
string GetOpTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
	{
		return "+";
	}
	case enOperationType::Sub:
	{
		return "-";
	}
	case enOperationType::Mul:
	{
		return "*";

	}
	case enOperationType::Div:
	{
		return "/";
	}
	default:
	{
		return "Mix";
	}
	}



}

void PrintQusetion(stQuizz& QuizInfo, int QuestionNumber)
{
	cout << "\nQuestion " << QuestionNumber + 1 << "/" << QuizInfo.NumberOfQuestions << endl;
	cout << QuizInfo.QuestionList[QuestionNumber].Number1 << endl;
	cout << QuizInfo.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(QuizInfo.QuestionList[QuestionNumber].OperationType);
	cout << "\n------------\n";

}
void SetScreenColor(bool Answer)
{
	if (Answer == true)
	{
		system("color 2F");

	}
	else
	{

		system("color 4F");
		cout << "\a";
	}

}
void CorrectTheQuestionAnswer(stQuizz& Quizzinfo, int QuestionNumber)
{
	if (Quizzinfo.QuestionList[QuestionNumber].PlayerAnser == Quizzinfo.QuestionList[QuestionNumber].CorrectAnser)
	{
		Quizzinfo.QuestionList[QuestionNumber].AnswerResult = true;
		Quizzinfo.NumberOfRightQuestions++;
		cout << "\nRight Answer :) \n";

	}
	else
	{
		Quizzinfo.QuestionList[QuestionNumber].AnswerResult = false;
		Quizzinfo.NumberOfWrongQuestions++;
		cout << "\nWrong Answer :(  ";
		cout << "\nThe right answer is : ";
		cout << Quizzinfo.QuestionList[QuestionNumber].CorrectAnser;

	}
	cout << endl;

	SetScreenColor(Quizzinfo.QuestionList[QuestionNumber].AnswerResult);

}
int ReadPlayerAnswer()
{
	int Number;
	cin >> Number;
	return Number;
}
void AskAndCorrectQuestionAnswer(stQuizz& QuizzInfo)
{

	for (int QuestionNumber = 0; QuestionNumber < QuizzInfo.NumberOfQuestions; QuestionNumber++)
	{
		PrintQusetion(QuizzInfo, QuestionNumber);
		QuizzInfo.QuestionList[QuestionNumber].PlayerAnser = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(QuizzInfo, QuestionNumber);
	}

	//QuizzInfo.IsPass = (QuizzInfo.NumberOfRightQuestions >= QuizzInfo.NumberOfWrongQuestions);


	if (QuizzInfo.NumberOfRightQuestions >= QuizzInfo.NumberOfWrongQuestions)
	{
		QuizzInfo.IsPass = true;
	}
	else
	{
		QuizzInfo.IsPass = false;
	}



}
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
	{
		return Number1 + Number2;
		break;
	}
	case enOperationType::Sub:
	{
		return Number1 - Number2;
		break;
	}
	case enOperationType::Mul:
	{
		return Number1 * Number2;
		break;
	}
	case enOperationType::Div:
	{
		return Number1 / Number2;
		break;

	}
	default:

		return Number1 + Number2;

	}
}
stQuiestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}
	if (OperationType == enOperationType::MixOp)
	{

		OperationType = (enOperationType)RandomNumber(1, 4);

	}

	stQuiestion Question;
	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{

	case enQuestionLevel::Easy:
	{
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnser = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	case enQuestionLevel::Med:
	{
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnser = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	case enQuestionLevel::Hard:
	{
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnser = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}

	}

	return Question;


}
void GenerateQuizzQuestions(stQuizz& QuizzInfo)
{

	for (int Question = 0; Question < QuizzInfo.NumberOfQuestions; Question++)
	{

		QuizzInfo.QuestionList[Question] = GenerateQuestion(QuizzInfo.QuestionsLevel, QuizzInfo.OperationType);
	}

}
string GetFinalResultsText(bool Answer)
{
	if (Answer == true)
	{
		return  "Passed :)";
	}
	else
	{
		return "Failed :(";
	}



}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrofQuestionsLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrofQuestionsLevelText[QuestionLevel - 1];


}
void PrintQuizzResults(stQuizz QuizzInfo)
{

	cout << "\n-------------------------------\n\n";
	cout << "Final Results is : " << GetFinalResultsText(QuizzInfo.IsPass) << endl;
	cout << "\n-------------------------------\n\n";
	cout << "Number Of Question      : " << QuizzInfo.NumberOfQuestions << endl;
	cout << "Questions Level         : " << GetQuestionLevelText(QuizzInfo.QuestionsLevel) << endl;
	cout << "Operation Type          : " << GetOpTypeSymbol(QuizzInfo.OperationType) << endl;
	cout << "Number Of Right Answers : " << QuizzInfo.NumberOfRightQuestions << endl;
	cout << "Number Of Wrong Answers : " << QuizzInfo.NumberOfWrongQuestions << endl;
	cout << "\n-------------------------------\n\n";




}
void PlayMathGame()
{
	stQuizz QuizzInfo;
	QuizzInfo.NumberOfQuestions = ReadHowManyQuestion();
	QuizzInfo.QuestionsLevel = ReadQuestionLevel();
	QuizzInfo.OperationType = ReadOperationType();


	GenerateQuizzQuestions(QuizzInfo);
	AskAndCorrectQuestionAnswer(QuizzInfo);
	PrintQuizzResults(QuizzInfo);


}


void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char Answer = 'y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "Do You Want To Play Again ? y/n ? ";
		cin >> Answer;
	} while (Answer == 'Y' || Answer == 'y');


}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}








