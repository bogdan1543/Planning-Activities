#ifndef LAB6_7_UNDO_H
#define LAB6_7_UNDO_H

#include "../domain/activity.h"
#include "../repos/repository.h"

class Undo{
public:
    virtual ~Undo() = default;
    virtual void doUndo() = 0;
};

class UndoAdd : public Undo{
    Activity addedActivity;
    AbsRepository& repo;
public:
    UndoAdd(AbsRepository& repository, const Activity& activity): addedActivity(activity), repo(repository){}

    void doUndo() override{
        repo.del(addedActivity);
    }
};

class UndoDelete : public Undo{
    Activity deletedActivity;
    AbsRepository& repo;
public:
    UndoDelete(AbsRepository& repository, const Activity& activity): deletedActivity(activity), repo(repository){}

    void doUndo() override{
        repo.add(deletedActivity);
    }
};

class UndoModify : public Undo{
    Activity modifiedActivity;
    AbsRepository& repo;
public:
    UndoModify(AbsRepository& repository, const Activity& activity): modifiedActivity(activity), repo(repository){}

    void doUndo() override{
        repo.modify(modifiedActivity);
    }
};

#endif //LAB6_7_UNDO_H
