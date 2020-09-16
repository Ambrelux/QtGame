#ifndef MODEL_H
#define MODEL_H


class Model
{
public:
    Model();

    class Player *getPlayer() const;
    void setPlayer(Player *value);

    void resetModel();

private:
    Player *player;
};

#endif // MODEL_H
