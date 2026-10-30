#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <ctime>
using namespace std;

// Smart Traffic Monitoring and Congestion Management System
// OOP concepts: encapsulation, inheritance, abstraction, polymorphism, composition,
// STL vectors, templates, file handling, and exception handling.

string cleanField(string s) {
    for (char &c : s) if (c == '|') c = '/';
    return s;
}

string readLine(const string &prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int readInt(const string &prompt, int minimum = 0) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        int value; char extra;
        if (ss >> value && !(ss >> extra) && value >= minimum) return value;
        cout << "Invalid input. Enter a whole number >= " << minimum << ".\n";
    }
}

double readDouble(const string &prompt, double minimum = 0.0) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        double value; char extra;
        if (ss >> value && !(ss >> extra) && value >= minimum) return value;
        cout << "Invalid input. Enter a number >= " << minimum << ".\n";
    }
}

// Small template function: displays any vector of printable objects.
template <typename T>
void displayCollection(const vector<T> &items, const string &heading) {
    cout << "\n--- " << heading << " ---\n";
    if (items.empty()) { cout << "No records found.\n"; return; }
    for (const auto &item : items) item.display();
}

template <typename T>
void displayCollection(const vector<T*> &items, const string &heading) {
    cout << "\n--- " << heading << " ---\n";
    if (items.empty()) { cout << "No records found.\n"; return; }
    for (const auto *item : items) if (item) item->display();
}

class Road {
private:
    int id;
    string name, startPoint, endPoint;
    double lengthKm;
public:
    Road(int i, string n, string s, string e, double l)
        : id(i), name(cleanField(n)), startPoint(cleanField(s)), endPoint(cleanField(e)), lengthKm(l) {
        if (id <= 0 || lengthKm <= 0) throw invalid_argument("Road ID and length must be positive.");
    }
    int getId() const { return id; }
    string getName() const { return name; }
    void display() const {
        cout << "Road ID: " << id << " | " << name << " | " << startPoint << " -> " << endPoint
             << " | Length: " << lengthKm << " km\n";
    }
    string serialize() const { ostringstream o; o << id << '|' << name << '|' << startPoint << '|' << endPoint << '|' << lengthKm; return o.str(); }
};

class Intersection {
private:
    int id;
    string name, location;
public:
    Intersection(int i, string n, string l) : id(i), name(cleanField(n)), location(cleanField(l)) {
        if (id <= 0) throw invalid_argument("Intersection ID must be positive.");
    }
    int getId() const { return id; }
    void display() const { cout << "Intersection ID: " << id << " | " << name << " | Location: " << location << '\n'; }
    string serialize() const { return to_string(id) + "|" + name + "|" + location; }
};

class Vehicle {
private:
    int id;
    string registration, type, roadName;
public:
    Vehicle(int i, string r, string t, string road) : id(i), registration(cleanField(r)), type(cleanField(t)), roadName(cleanField(road)) {
        if (id <= 0 || registration.empty()) throw invalid_argument("Vehicle ID must be positive and registration cannot be empty.");
    }
    void display() const { cout << "Vehicle ID: " << id << " | Reg: " << registration << " | Type: " << type << " | Road: " << roadName << '\n'; }
    string serialize() const { return to_string(id) + "|" + registration + "|" + type + "|" + roadName; }
};

class TrafficSignal {
private:
    int id, greenSeconds;
    string intersectionName, state;
public:
    TrafficSignal(int i, string intersection, int seconds, string s)
        : id(i), greenSeconds(seconds), intersectionName(cleanField(intersection)), state(s) {
        if (id <= 0 || greenSeconds < 1 || greenSeconds > 300) throw invalid_argument("Signal ID must be positive and green time must be 1-300 seconds.");
        if (state != "RED" && state != "YELLOW" && state != "GREEN") throw invalid_argument("Signal state must be RED, YELLOW, or GREEN.");
    }
    void display() const { cout << "Signal ID: " << id << " | Intersection: " << intersectionName << " | State: " << state << " | Green time: " << greenSeconds << " sec\n"; }
    string serialize() const { return to_string(id) + "|" + intersectionName + "|" + to_string(greenSeconds) + "|" + state; }
};

class TrafficReading {
private:
    int id, vehicleCount;
    double averageSpeed;
    string roadName, congestion;
public:
    TrafficReading(int i, string road, int count, double speed)
        : id(i), vehicleCount(count), averageSpeed(speed), roadName(cleanField(road)) {
        if (id <= 0 || averageSpeed < 0 || averageSpeed > 250) throw invalid_argument("Invalid reading values.");
        if (vehicleCount >= 80 || averageSpeed < 15) congestion = "HIGH";
        else if (vehicleCount >= 40 || averageSpeed < 30) congestion = "MODERATE";
        else congestion = "LOW";
    }
    string getCongestion() const { return congestion; }
    void display() const { cout << "Reading ID: " << id << " | Road: " << roadName << " | Vehicles: " << vehicleCount << " | Avg speed: " << averageSpeed << " km/h | Congestion: " << congestion << '\n'; }
    string serialize() const { ostringstream o; o << id << '|' << roadName << '|' << vehicleCount << '|' << averageSpeed << '|' << congestion; return o.str(); }
};

// Abstraction and runtime polymorphism: every incident provides its own type description.
class TrafficIncident {
protected:
    int id;
    string roadName, description, status;
public:
    TrafficIncident(int i, string road, string desc, string st)
        : id(i), roadName(cleanField(road)), description(cleanField(desc)), status(st) {
        if (id <= 0) throw invalid_argument("Incident ID must be positive.");
    }
    virtual string getType() const = 0;
    string getRoadName() const { return roadName; }
    string getStatus() const { return status; }
    virtual void display() const {
        cout << "Incident ID: " << id << " | Type: " << getType() << " | Road: " << roadName
             << " | Description: " << description << " | Status: " << status << '\n';
    }
    virtual string serialize() const { return to_string(id) + "|" + getType() + "|" + roadName + "|" + description + "|" + status; }
    virtual ~TrafficIncident() = default;
};

class AccidentIncident : public TrafficIncident {
public:
    AccidentIncident(int i, string road, string desc, string st) : TrafficIncident(i, road, desc, st) {}
    string getType() const override { return "ACCIDENT"; }
};
class RoadblockIncident : public TrafficIncident {
public:
    RoadblockIncident(int i, string road, string desc, string st) : TrafficIncident(i, road, desc, st) {}
    string getType() const override { return "ROADBLOCK"; }
};

class User {
private:
    string username, password, role;
public:
    User(string u = "", string p = "", string r = "NORMAL")
        : username(u), password(p), role(r) {}
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    bool isAdmin() const { return role == "ADMIN"; }
    void display() const {
        cout << "Logged in as: " << username << " (" << role << ")\n";
    }
    string serialize() const { return username + "|" + password + "|" + role; }
};

class TrafficManagementSystem {
private:
    vector<Road> roads;
    vector<Intersection> intersections;
    vector<Vehicle> vehicles;
    vector<TrafficSignal> signals;
    vector<TrafficReading> readings;
    vector<TrafficIncident*> incidents; // base-class pointers demonstrate polymorphism
    User currentUser;
    vector<User> users;

    void logActivity(const string &action) const {
        ofstream file("activity_log.txt", ios::app);
        if (!file) {
            cout << "Warning: could not write activity_log.txt\n";
            return;
        }
        time_t now = time(nullptr);
        tm *local = localtime(&now);
        char stamp[32] = "unknown-time";
        if (local) strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", local);
        file << stamp << "|" << currentUser.getUsername() << "|"
             << currentUser.getRole() << "|" << cleanField(action) << '\n';
    }

    void loadUsers() {
        users.clear();
        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            stringstream s(line);
            string u, p, r;
            if (getline(s, u, '|') && getline(s, p, '|') && getline(s, r, '|')) {
                if (!u.empty() && (r == "ADMIN" || r == "NORMAL"))
                    users.emplace_back(u, p, r);
            }
        }
        bool hasAdmin = false;
        for (const auto &u : users) if (u.isAdmin()) hasAdmin = true;
        if (!hasAdmin) users.emplace_back("admin", "admin123", "ADMIN");
        saveUsers();
    }

    void saveUsers() const {
        ofstream file("users.txt");
        if (!file) throw runtime_error("Could not open users.txt for writing.");
        for (const auto &u : users) file << u.serialize() << '\n';
    }

    bool usernameExists(const string &name) const {
        for (const auto &u : users) if (u.getUsername() == name) return true;
        return false;
    }

    bool authenticate() {
        loadUsers();
        while (true) {
            cout << "\n========== ACCOUNT MENU ==========\n"
                 << "1. Login\n2. Register normal user\n0. Exit\n";
            int choice = readInt("Choose: ", 0);
            if (choice == 0) return false;
            if (choice == 2) {
                string name = readLine("Choose username: ");
                if (name.empty() || name.find('|') != string::npos) {
                    cout << "Username cannot be empty or contain '|'.\n";
                    continue;
                }
                if (usernameExists(name)) {
                    cout << "That username already exists.\n";
                    continue;
                }
                string pass = readLine("Choose password: ");
                if (pass.size() < 4 || pass.find('|') != string::npos) {
                    cout << "Password must be at least 4 characters and cannot contain '|'.\n";
                    continue;
                }
                users.emplace_back(name, pass, "NORMAL");
                saveUsers();
                currentUser = User(name, pass, "NORMAL");
                logActivity("Registered normal user");
                logActivity("Login successful");
                return true;
            }
            if (choice == 1) {
                string name = readLine("Username: ");
                string pass = readLine("Password: ");
                bool found = false;
                for (const auto &u : users) {
                    if (u.getUsername() == name && u.getPassword() == pass) {
                        currentUser = u;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    logActivity("Login successful");
                    return true;
                }
                cout << "Invalid username or password.\n";
                currentUser = User(name, "", "UNKNOWN");
                logActivity("Failed login attempt");
            } else {
                cout << "Invalid account-menu choice.\n";
            }
        }
    }

    bool requireAdmin(const string &operation) const {
        if (currentUser.isAdmin()) return true;
        cout << "Access denied: only an ADMIN can " << operation << ".\n";
        return false;
    }

    template <typename T>
    void saveRecords(const vector<T> &items, const string &filename) {
        ofstream file(filename);
        if (!file) throw runtime_error("Could not open " + filename + " for writing.");
        for (const auto &item : items) file << item.serialize() << '\n';
    }
    void saveIncidents() {
        ofstream file("incidents.txt");
        if (!file) throw runtime_error("Could not open incidents.txt for writing.");
        for (const auto *item : incidents) file << item->serialize() << '\n';
    }
    int nextId(const string &kind) const {
        if (kind == "road") return static_cast<int>(roads.size()) + 1;
        if (kind == "intersection") return static_cast<int>(intersections.size()) + 1;
        if (kind == "vehicle") return static_cast<int>(vehicles.size()) + 1;
        if (kind == "signal") return static_cast<int>(signals.size()) + 1;
        if (kind == "reading") return static_cast<int>(readings.size()) + 1;
        return static_cast<int>(incidents.size()) + 1;
    }
    void loadSimpleFiles() {
        // The files are append-free snapshots; loading keeps records between program runs.
        string line;
        ifstream f;
        f.open("roads.txt");
        while (getline(f, line)) { stringstream s(line); string a,b,c,d,e; if(getline(s,a,'|')&&getline(s,b,'|')&&getline(s,c,'|')&&getline(s,d,'|')&&getline(s,e,'|')) try { roads.emplace_back(stoi(a),b,c,d,stod(e)); } catch(...) {} }
        f.close(); f.open("intersections.txt");
        while (getline(f,line)) { stringstream s(line); string a,b,c; if(getline(s,a,'|')&&getline(s,b,'|')&&getline(s,c,'|')) try { intersections.emplace_back(stoi(a),b,c); } catch(...) {} }
        f.close(); f.open("vehicles.txt");
        while (getline(f,line)) { stringstream s(line); string a,b,c,d; if(getline(s,a,'|')&&getline(s,b,'|')&&getline(s,c,'|')&&getline(s,d,'|')) try { vehicles.emplace_back(stoi(a),b,c,d); } catch(...) {} }
        f.close(); f.open("signals.txt");
        while (getline(f,line)) { stringstream s(line); string a,b,c,d; if(getline(s,a,'|')&&getline(s,b,'|')&&getline(s,c,'|')&&getline(s,d,'|')) try { signals.emplace_back(stoi(a),b,stoi(c),d); } catch(...) {} }
        f.close(); f.open("readings.txt");
        while (getline(f,line)) { stringstream s(line); string a,b,c,d,e; if(getline(s,a,'|')&&getline(s,b,'|')&&getline(s,c,'|')&&getline(s,d,'|')) try { readings.emplace_back(stoi(a),b,stoi(c),stod(d)); } catch(...) {} }
        // Incident records are loaded as their appropriate derived class.
        f.close(); f.open("incidents.txt");
        while (getline(f,line)) { stringstream s(line); string a,t,b,c,d; if(getline(s,a,'|')&&getline(s,t,'|')&&getline(s,b,'|')&&getline(s,c,'|')&&getline(s,d,'|')) try { if(t=="ACCIDENT") incidents.push_back(new AccidentIncident(stoi(a),b,c,d)); else if(t=="ROADBLOCK") incidents.push_back(new RoadblockIncident(stoi(a),b,c,d)); } catch(...) {} }
    }
    void saveAll() {
        saveRecords(roads,"roads.txt"); saveRecords(intersections,"intersections.txt");
        saveRecords(vehicles,"vehicles.txt"); saveRecords(signals,"signals.txt");
        saveRecords(readings,"readings.txt"); saveIncidents();
    }
    void addRoad() {
        string name=readLine("Road name: "), start=readLine("Start point: "), end=readLine("End point: ");
        double length=readDouble("Length in km: ",0.01);
        roads.emplace_back(nextId("road"),name,start,end,length); saveAll(); cout << "Road added and saved.\n";
    }
    void addIntersection() {
        string name=readLine("Intersection name: "), location=readLine("Location/area: ");
        intersections.emplace_back(nextId("intersection"),name,location); saveAll(); cout << "Intersection added and saved.\n";
    }
    void addVehicle() {
        string reg=readLine("Registration number: "), type=readLine("Vehicle type (Car/Bike/Bus/Truck): "), road=readLine("Current road: ");
        vehicles.emplace_back(nextId("vehicle"),reg,type,road); saveAll(); cout << "Vehicle added and saved.\n";
    }
    void addSignal() {
        string intersection=readLine("Intersection name: ");
        int green=readInt("Green duration (1-300 seconds): ",1);
        while(green>300) { cout << "Maximum is 300 seconds.\n"; green=readInt("Green duration (1-300 seconds): ",1); }
        string state=readLine("Signal state (RED/YELLOW/GREEN): ");
        for(char &c:state) c=static_cast<char>(toupper(static_cast<unsigned char>(c)));
        signals.emplace_back(nextId("signal"),intersection,green,state); saveAll(); cout << "Signal added and saved.\n";
    }
    void addReading() {
        string road=readLine("Road name: "); int count=readInt("Vehicle count: ",0); double speed=readDouble("Average speed in km/h: ",0);
        readings.emplace_back(nextId("reading"),road,count,speed); saveAll(); cout << "Traffic reading recorded.\n";
        cout << "Calculated congestion level: " << readings.back().getCongestion() << '\n';
    }
    void addIncident() {
        cout << "1. Accident\n2. Roadblock\n"; int type=readInt("Choose incident type: ",1);
        while(type>2) { cout << "Choose 1 or 2.\n"; type=readInt("Choose incident type: ",1); }
        string road=readLine("Road name: "), desc=readLine("Description: ");
        string status = "Reported";
        int id=nextId("incident");
        if(type==1) incidents.push_back(new AccidentIncident(id,road,desc,status)); else incidents.push_back(new RoadblockIncident(id,road,desc,status));
        saveAll(); cout << "Incident recorded and saved.\n";
    }

    void searchRoads() const {
        string query = readLine("Search road name (partial match): ");
        bool found = false;
        for (const auto &r : roads) {
            string name = r.getName(), q = query;
            transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return static_cast<char>(tolower(c)); });
            transform(q.begin(), q.end(), q.begin(), [](unsigned char c){ return static_cast<char>(tolower(c)); });
            if (name.find(q) != string::npos) { r.display(); found = true; }
        }
        if (!found) cout << "No matching roads found.\n";
        logActivity("Searched roads for: " + query);
    }

    void filterReadings() const {
        cout << "1. HIGH congestion\n2. MODERATE congestion\n3. LOW congestion\n";
        int choice = readInt("Filter by level: ", 1);
        while (choice > 3) { cout << "Choose 1, 2, or 3.\n"; choice = readInt("Filter by level: ", 1); }
        string wanted = choice == 1 ? "HIGH" : (choice == 2 ? "MODERATE" : "LOW");
        bool found = false;
        for (const auto &r : readings) if (r.getCongestion() == wanted) { r.display(); found = true; }
        if (!found) cout << "No readings found for " << wanted << ".\n";
        logActivity("Filtered traffic readings: " + wanted);
    }

    void searchIncidents() const {
        cout << "1. Search by road name\n2. Filter by status\n";
        int choice = readInt("Choose filter: ", 1);
        while (choice > 2) { cout << "Choose 1 or 2.\n"; choice = readInt("Choose filter: ", 1); }
        string query = readLine(choice == 1 ? "Road name (partial match): " : "Status (e.g. Reported, Open, In Progress, Resolved): ");
        string q = query;
        transform(q.begin(), q.end(), q.begin(), [](unsigned char c){ return static_cast<char>(tolower(c)); });
        bool found = false;
        for (const auto *incident : incidents) {
            if (!incident) continue;
            string value = (choice == 1) ? incident->getRoadName() : incident->getStatus();
            transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return static_cast<char>(tolower(c)); });
            if (value.find(q) != string::npos) { incident->display(); found = true; }
        }
        if (!found) cout << "No matching incidents found.\n";
        logActivity("Searched incidents");
    }

    void updateIncidentStatus() {
        if (incidents.empty()) { cout << "No incidents to update.\n"; return; }
        displayCollection(incidents, "INCIDENTS");
        int id = readInt("Enter incident ID to update: ", 1);
        for (size_t index = 0; index < incidents.size(); ++index) {
            TrafficIncident *incident = incidents[index];
            if (incident && incident->serialize().rfind(to_string(id) + "|", 0) == 0) {
                string status = readLine("New status (Reported/In Progress/Resolved): ");
                string normalized = status;
                transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char c){ return static_cast<char>(tolower(c)); });
                if (normalized == "reported") status = "Reported";
                else if (normalized == "in progress") status = "In Progress";
                else if (normalized == "resolved") status = "Resolved";
                else { cout << "Invalid status. No changes made.\n"; return; }
                // Status is protected in the base class, so reconstruct the matching derived object.
                string data = incident->serialize();
                stringstream ss(data);
                string sid, type, road, desc, oldStatus;
                getline(ss, sid, '|'); getline(ss, type, '|'); getline(ss, road, '|'); getline(ss, desc, '|'); getline(ss, oldStatus, '|');
                TrafficIncident *replacement = nullptr;
                if (type == "ACCIDENT") replacement = new AccidentIncident(id, road, desc, status);
                else replacement = new RoadblockIncident(id, road, desc, status);
                delete incident;
                incidents[index] = replacement;
                saveAll();
                logActivity("Updated incident " + to_string(id) + " status to " + status);
                cout << "Incident status updated.\n";
                return;
            }
        }
        cout << "Incident ID not found.\n";
    }

    void viewActivityLog() const {
        ifstream file("activity_log.txt");
        string line;
        cout << "\n--- ACTIVITY LOG ---\n";
        if (!file) { cout << "No activity log yet.\n"; return; }
        while (getline(file, line)) cout << line << '\n';
    }

    void showDashboard() const {
        cout << "\n========== TRAFFIC DASHBOARD ==========\n";
        cout << "Roads: " << roads.size() << " | Intersections: " << intersections.size()
             << " | Vehicles: " << vehicles.size() << " | Signals: " << signals.size()
             << " | Readings: " << readings.size() << " | Incidents: " << incidents.size() << '\n';
        int high=0, moderate=0, low=0;
        for(const auto &r:readings) { if(r.getCongestion()=="HIGH") high++; else if(r.getCongestion()=="MODERATE") moderate++; else low++; }
        cout << "Congestion summary (from recorded readings): HIGH=" << high << ", MODERATE=" << moderate << ", LOW=" << low << '\n';
        cout << "=======================================\n";
    }
public:
    TrafficManagementSystem() { loadSimpleFiles(); }
    ~TrafficManagementSystem() { for(auto *item:incidents) delete item; }
    void run() {
        if (!authenticate()) { cout << "Exiting system. Goodbye!\n"; return; }
        currentUser.display();
        while(true) {
            cout << "\n========== SMART TRAFFIC MANAGEMENT ==========\n"
                 << "1. Add road (ADMIN)\n2. View roads\n3. Add intersection (ADMIN)\n4. View intersections\n"
                 << "5. Register vehicle (ADMIN)\n6. View vehicles\n7. Add traffic signal (ADMIN)\n8. View signals\n"
                 << "9. Record traffic reading (ADMIN)\n10. View traffic readings\n11. Report incident\n12. View incidents\n"
                 << "13. Traffic dashboard\n14. Save all records (ADMIN)\n"
                 << "15. Search roads\n16. Filter traffic readings by congestion\n17. Search/filter incidents\n"
                 << "18. Update incident status (ADMIN)\n19. View activity log (ADMIN)\n"
                 << "20. Logout\n0. Exit\n";
            int choice = readInt("Enter choice: ", 0);
            try {
                switch (choice) {
                    case 1: if (requireAdmin("add roads")) addRoad(); break;
                    case 2: displayCollection(roads, "ROADS"); logActivity("Viewed roads"); break;
                    case 3: if (requireAdmin("add intersections")) addIntersection(); break;
                    case 4: displayCollection(intersections, "INTERSECTIONS"); logActivity("Viewed intersections"); break;
                    case 5: if (requireAdmin("register vehicles")) addVehicle(); break;
                    case 6: displayCollection(vehicles, "VEHICLES"); logActivity("Viewed vehicles"); break;
                    case 7: if (requireAdmin("manage traffic signals")) addSignal(); break;
                    case 8: displayCollection(signals, "TRAFFIC SIGNALS"); logActivity("Viewed signals"); break;
                    case 9: if (requireAdmin("record traffic readings")) addReading(); break;
                    case 10: displayCollection(readings, "TRAFFIC READINGS"); logActivity("Viewed traffic readings"); break;
                    case 11: addIncident(); break;
                    case 12: displayCollection(incidents, "TRAFFIC INCIDENTS"); logActivity("Viewed incidents"); break;
                    case 13: showDashboard(); logActivity("Viewed dashboard"); break;
                    case 14: if (requireAdmin("save all records")) { saveAll(); logActivity("Saved all records"); cout << "All records saved.\n"; } break;
                    case 15: searchRoads(); break;
                    case 16: filterReadings(); break;
                    case 17: searchIncidents(); break;
                    case 18: if (requireAdmin("update incident status")) updateIncidentStatus(); break;
                    case 19: if (requireAdmin("view activity log")) viewActivityLog(); break;
                    case 20: logActivity("Logout"); if (!authenticate()) return; currentUser.display(); break;
                    case 0: saveAll(); logActivity("Exit"); cout << "Data saved. Exiting system. Goodbye!\n"; return;
                    default: cout << "Invalid menu choice. Try again.\n";
                }
            } catch(const exception &e) { cout << "Error: " << e.what() << '\n'; }
        }
    }
};

int main() {
    try {
        TrafficManagementSystem system;
        system.run();
    } catch(const exception &e) {
        cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
