#include "InvalidIDException.h"
#include "Team.h"

bool Team::setMemberID(int index, string idNum) {
    try {
        Employee* employee = getMember(index);
        employee->setIDNum(idNum);
        cout << "Member " << index << ": ID set to " << idNum << endl;
        return true;
    } catch (InvalidIDException& e) {
        // The most derived type must come first.
        cout << "Member " << index << ": bad ID [" << e.getBadID() << "]: " << e.what() << endl;
    } catch (Exception& e) {
        cout << "Member " << index << ": " << e.what() << endl;
    }
    return false;
}
