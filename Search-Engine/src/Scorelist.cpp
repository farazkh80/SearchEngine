#include "../inc/Scorelist.h"
using namespace std;

Scorelist::~Scorelist()
{
	if (next != NULL)
		delete(next);
}
// Function for creating a score list containing the ids of documents
// containing a specific word
void Scorelist::insert(int did)
{
	if (id == did)
		return;
	if (id == -1)
		id = did;
	else
	{
		if (next == NULL)
			next = new Scorelist(did);
		else
			next->insert(did);
	}
}