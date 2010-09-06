#ifndef _INCL_GUARD_VER
#define _INCL_GUARD_VER

#include <string>
#include "cv.h"
#include "highgui.h"

/**
* Structure of Face Images.
*/
typedef struct
{
  IplImage** faces; /**< Array of IplImage - of Faces */
  int count;/**< Total Number of Images */
}
structFaceImages;

/**
* Structure of All Sets.
*/
typedef struct
{
  char** setName;/**< Name of the Set , This is a Unique Autogenerated Name */
  structFaceImages *faceImages;/**< Array of Structs of Face Images @see structFaceImages */
  char** setFilePathThumbnails/**< Array of Paths to Sample Images of Each Set , Currently 1.jpg */;
  int count/**< Total Number of Sets */;
}
setFace;

/**
* Verifier class. This is the Verifier class used to verify a face.
*/
class verifier
{
  private:
    /**
    * Returns a unique name required to create a new set
    * @result returns a unique string, uses date+time
    * @see addFaceSet
    */
    std::string createSetDir() const;

    /**
    * Linux user struct
    */
    struct passwd* userStruct;

  public:
    /**
    * Contains the path $HOME/.pam-face-authentication/faces
    */
    std::string facesDirectory;
    
    /**
    * Contains the Path $HOME/.pam-face-authentication/model
    */
    std::string modelDirectory;
    
    /**
    * Contains the Path $HOME/.pam-face-authentication/config
    */
    std::string configDirectory;

    /**
    * The Constructor
    * Finds the uid of the user running the verifier object
    * and sets up the internal information accordingly
    */
    verifier();

    /**
    * The Constructor overloaded
    * In case the user wants to override the uid, for example, during verification
    */
    verifier(uid_t userID);

    /**
    * The destructor
    */
    virtual ~verifier();

    /**
    * Creates the MACE Filter and LBP Feature Hist
    * It creates $HOME/.pam-face-authentication/model/$SET NAME_(FACE | EYE | INSIDE_FACE)_(MACE | LBP).XML
    * @param setName, if set name is NULL, then all the faces sets are retrained
    */
    void createBiometricModels(char* setName);

    /**
    * Adds a set of face images and calls createBiometricModels
    * @param set, Set of IplImage of Faces
    * @param size, Size of set
    * @see createBiometricModels
    */
    void addFaceSet(IplImage** set, int size);
    //allFaces* getFaceImagesFromAllSet();

    /**
    * Removes the Set from $HOME/.pam-face-authentication/faces/$SETNAME/ 
    * and its models call createBiometricModels afterwards
    * @param setName, Name of the Set
    * @see createBiometricModels
    */
    void removeFaceSet(char* setName);

    /**
    * Returns all sets of face images of the current user
    * @result setFace - returns the all face sets in a setFace structure
    * @see setFace
    */
    setFace* getFaceSet();

    //TODO
    /**
    * VerifyFace - Does the verification of the param image with the current user
    * @result 1 - Verified, 0 - Imposter
    */
    int verifyFace(IplImage* face);

};

#endif // _INCL_GUARD_VER