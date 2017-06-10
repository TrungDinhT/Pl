#include <iostream>
#include <string>
#include <ctime>

using namespace std;

enum Etat {EN_ATTENTE, EN_COURS, TERMINE};


class NotesException{
    public:
        NotesException(const string& message):info(message){}
        string getInfo() const {return info;}
    private:
        string info;
};


class Version {
    protected:
        string titre;
        time_t dateModif;
    public:
        Version(const string& titre):titre(titre),dateModif(time(0)){}
        time_t getDateModif() const {return dateModif;}
        string getTitre() const {return titre;}
        void setTitre(const string& t){titre=t;}
};

class Note {
    private:
        string id;
        time_t dateCreation;
        bool active; //true = active, false = archive
        Version** versions;
        unsigned int nbVersions;
        unsigned int nbVersionsMax;
        //void addVersion(Version* v);
        //void addVersion(const string& ti);
        Note(const Note& n);
        Note& operator=(const Note& n);
    public:
        Note(const string& titre): id(), dateCreation(time(0)), active(true), versions(NULL){}
        ~Note();
        //autoLoad();
        virtual string createId()=0;
        //void setId(const string& newId);
        void changerActive(bool a){active=a;}
        string getId() const {return id;}
        bool getActive() const {return active;}
        time_t getDateCreation() const {return dateCreation;}

        class Iterator {
                friend class Note;
                Version** currentV;
                unsigned int nbRemain;
                Iterator(Version** v, unsigned nb):currentV(v),nbRemain(nb){}
            public:
                Iterator():currentV(NULL),nbRemain(0){}
                bool isDone() const { return nbRemain==0; }
                void next() {
                    if (isDone())
                        throw NotesException("error, next on an iterator which is done");
                    nbRemain--;
                    currentV++;
                }
                Version& current() const {
                    if (isDone())
                        throw NotesException("error, indirection on an iterator which is done");
                    return **currentV;
                }
            };
        Iterator getIterator() {
            return Iterator(versions,nbVersions);
        }
};

class NoteManager {
    private:
        string filename;
        static NoteManager* instance;
        Note** notes;
        unsigned int nbNotes;
        unsigned int nbNotesMax;
        void addNote(Note* n);
        void addNote(const string& ti);
        NoteManager();
        ~NoteManager();
        NoteManager(const NoteManager& m);
        NoteManager& operator=(const NoteManager& m);
    public:
        //Note& getNewNote(const string& id);
        Note& getNote(const string& id);
        void setFilename(const string& f){filename=f;}
        //deleteNote(const string id);
        void load(const string f);
        //save(const string f);
        void save() const ;
        static NoteManager& getManager();
        static void freeManager();

        class Iterator {
                friend class NoteManager;
                Note** currentN;
                unsigned int nbRemain;
                Iterator(Note** n, unsigned nb):currentN(n),nbRemain(nb){}
            public:
                Iterator():currentN(NULL),nbRemain(0){}
                bool isDone() const { return nbRemain==0; }
                void next() {
                    if (isDone())
                        throw NotesException("error, next on an iterator which is done");
                    nbRemain--;
                    currentN++;
                }
                Note& current() const {
                    if (isDone())
                        throw NotesException("error, indirection on an iterator which is done");
                    return **currentN;
                }
            };
        Iterator getIterator() {
            return Iterator(notes,nbNotes);
        }
};

class Article : public Version {
    private:
        string texte;
        string createId();
    public:
        Article(const string& ti, const string& te) : Version(ti), texte(te){}
        const string getTexte() const {return texte;}
        void setTexte(const string& t){texte=t;}
};

class Image : public Version {
    private:
        string description;
        string nomFichier;
        string createId();
    public:
        Image(const string& ti, const string& d, const string& f):Version(ti), description(d),nomFichier(f){}
        string getDesc() const {return description;}
        void setDesc(const string& desc){description=desc;}
        string getNomFichier() const {return nomFichier;}
};

class Tache : public Version {
    private :
        string action;
        int priorite;
        time_t dateEcheance;
        Etat statut;
        string createId();
    public:
        Tache(const string& ti, const string& a, int p, time_t& d, Etat& s):Version(ti), action(a), priorite(p), dateEcheance(d), statut(s){}
        string getAction() const {return action;}
        int getPriorite() const {return priorite;}
        time_t getDateEch() const {return dateEcheance;}
        Etat getStatut() const {return statut;}
        void setAction(const string& a) {action=a;}
        void setPriorite(const int p) {priorite=p;}
        void setDateEch(const time_t& d) {dateEcheance=d;}
        void setStatut(const Etat& s) {statut=s;}

};


