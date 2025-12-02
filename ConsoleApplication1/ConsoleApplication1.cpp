

#include <iostream>
#include<string>
#include<ctime>
#include<cmath>
using namespace std;
enum enQuestionLevel{EasyLevel=1,MedLevel=2,HardLevel=3,Mix=3};
enum enOperationType{Add=1,Sub=2,Mult=3,Div=4,MixOp=5};
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnwer = 0;
	bool AnswerResult = false;

};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestion;
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfwrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;

};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}

}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel,enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}
	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}
	Question.OperationType = OpType;
	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	}
	return Question;

}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz. OpType);
	}
}
enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add,[2] Sub ,[3] Mul,[4] Div,[5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType>5);
	return(enOperationType)OpType;
}
enQuestionLevel  ReadQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix ?";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel>4);
	return (enQuestionLevel)QuestionLevel;

}
short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How many questions do you want to anser ? ";
		cin >> NumberOfQuestions;
		
	} while (NumberOfQuestions < 1 || NumberOfQuestions>10);
	return NumberOfQuestions;
}
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnwer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfwrongAnswers++;
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is : ";
		Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-)\n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n__________" << endl;

}
void AskAndCorrectQuestionListAnswers(stQuizz Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnwer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "__________________________\n\n";
	cout << "Final Results is : " << GetFinalResultsText(Quizz.isPass);
	cout << "\n___________________________\n\n";
	cout << "Number of Question : " << Quizz.NumberOfQuestion << endl;
	cout << "Question Level       : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType                 : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong answers :" << Quizz.NumberOfwrongAnswers << endl;
	cout << "___________________________\n";

}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestion = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();
	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);


}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << endl << "Do you want to play again ? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0 ;
}
