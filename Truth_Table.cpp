#include "Includes.h"
//================================================================
Truth_Table::Truth_Table()
{};
Truth_Table::~Truth_Table()
{};

void Truth_Table::ReadActionParameters(ApplicationManager *pManager)
{}
//===========================================================
void Truth_Table::setUsedComp(ApplicationManager *pManager)
{
	Used=pManager->getselectedcomponent();
}
//===========================================================
void Truth_Table::Execute(ApplicationManager *pManager)
{

Input* PtrInput = pManager->getInput();
Output* PtrOutput = pManager->getOutput();
setUsedComp(pManager);
Point P;
if (Used->getCurrentGfxInfo().Center.y<=322)
{

switch (Used->getName())
{
	case AND_2 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-AND-2.jpg");
		break;
	case NAND_2 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NAND-2.jpg");
		break;
	case OR_2 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-OR-2.jpg");
		break;
	case NOR_2:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NOR-2.jpg");
		break;
	case XOR_2:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-XOR-2.jpg");
	case XNOR_2:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-XNOR-2.jpg");
		break;
	case AND_3:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-AND-3.jpg");
		break;
	case NAND_3 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NAND-3.jpg");
		break;
	case OR_3 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-OR-3.jpg");
		break;
	case NOR_3:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NOR-3.jpg");
		break;
	case XOR_3:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-XOR-3.jpg");
		break;
	case XNOR_3:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-XNOR-3.jpg");
		break;
	case AND_4:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-AND-4.jpg");
		break;
	case NAND_4 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NAND-4.jpg");
		break;
	case OR_4 :
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-OR-4.jpg");
		break;
	case NOR_4:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NOR-4.jpg");
		break;
	case XOR_4:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-XOR-4.jpg");
		break;
	case XNOR_4:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-XNOR-4.jpg");
		break;
	case BUFFER:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-BUFFER.jpg");
		break;
	case NOT:
		P=Used->getCurrentGfxInfo().DownRight;
		/*P.x=P.x+85;
		P.y=P.y+56;*/
		PtrOutput->drawTruthTable(P,"images//Truth-NOT.jpg");
		break;
	}
	}
	else
	{
		switch (Used->getName())
		{
		case AND_2 :
			P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-AND-2.jpg");
		break;
	case NAND_2 :
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-NAND-2.jpg");
		break;
	case OR_2 :
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-OR-2.jpg");
		break;
	case NOR_2:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-NOR-2.jpg");
		break;
	case XOR_2:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-XOR-2.jpg");
	case XNOR_2:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-XNOR-2.jpg");
		break;
	case AND_3:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-113;
		PtrOutput->drawTruthTable(P,"images//Truth-AND-3.jpg");
		break;
	case NAND_3 :
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-227;
		PtrOutput->drawTruthTable(P,"images//Truth-NAND-3.jpg");
		break;
	case OR_3 :
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-227;
		PtrOutput->drawTruthTable(P,"images//Truth-OR-3.jpg");
		break;
	case NOR_3:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-227;
		PtrOutput->drawTruthTable(P,"images//Truth-NOR-3.jpg");
		break;
	case XOR_3:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-227;
		PtrOutput->drawTruthTable(P,"images//Truth-XOR-3.jpg");
		break;
	case XNOR_3:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-227;
		PtrOutput->drawTruthTable(P,"images//Truth-XNOR-3.jpg");
		break;
	case AND_4:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-170;
		P.y=P.y-227;
		PtrOutput->drawTruthTable(P,"images//Truth-AND-4.jpg");
		break;
	case NAND_4 :
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-227;
		P.y=P.y-454;
		PtrOutput->drawTruthTable(P,"images//Truth-NAND-4.jpg");
		break;
	case OR_4 :
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-227;
		P.y=P.y-454;
		PtrOutput->drawTruthTable(P,"images//Truth-OR-4.jpg");
		break;
	case NOR_4:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-227;
		P.y=P.y-454;
		PtrOutput->drawTruthTable(P,"images//Truth-NOR-4.jpg");
		break;
	case XOR_4:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-227;
		P.y=P.y-454;
		PtrOutput->drawTruthTable(P,"images//Truth-XOR-4.jpg");
		break;
	case XNOR_4:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-227;
		P.y=P.y-454;
		PtrOutput->drawTruthTable(P,"images//Truth-XNOR-4.jpg");
		break;
	case BUFFER:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-98;
		P.y=P.y-76;
		PtrOutput->drawTruthTable(P,"images//Truth-BUFFER.jpg");
		break;
	case NOT:
		P=Used->getCurrentGfxInfo().UpLeft;
		P.x=P.x-98;
		P.y=P.y-76;
		PtrOutput->drawTruthTable(P,"images//Truth-NOT.jpg");
		break;
	}
}

}

void Truth_Table::unExecute(ApplicationManager *pManager)
{
}
