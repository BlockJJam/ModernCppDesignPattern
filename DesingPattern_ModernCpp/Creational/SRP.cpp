#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
using namespace std;

struct Journal
{
	string title;
	vector<string> entries;

	explicit Journal(const string& titile)
		:title(title)
	{
	}

	void add(const string& entry);

	// 저장소는 별개의 독립적인 이해관계다
	void save(const string& filename);
};

void Journal::add(const string& entry)\
{
	static int count = 1;
	entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
}

void Journal::save(const string& filename)
{
	ofstream ofs(filename);
	for (auto& s : entries)
		ofs << s << endl;
}

struct PersistenceManager
{
	static void save(const Journal& j, const string& filename)
	{
		ofstream ofs(filename);
		for (auto& s : j.entries)
			ofs << s << endl;
	}
};

void main()
{
	Journal journal("Dear Diary");
	journal.add("I ate a bug");
	journal.add("I cried today");

	//journal.save("diary.txt");

	PersistenceManager pm;
	pm.save(journal, "diary.txt");
}