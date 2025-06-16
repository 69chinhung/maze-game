#ifndef ELEMENT_H
#define ELEMENT_H

#include "icon.h"
#include "unit.h"
#include <iostream>
#include <vector>
class GameObject {

public:
  GameObject(Icon icon, Position pos = {0, 0});

  virtual ~GameObject();
  virtual void update();
  Icon getIcon() const;
  void setDirection(Direction);
  Vec2 getPosition() const;
 void setPosition(const Position& pos) { _pos = pos; }
protected:
  Direction _dir;
  Vec2 _pos;
  Icon _icon;
};

inline Icon GameObject::getIcon() const { return _icon; }

inline Vec2 GameObject::getPosition() const { return _pos; }
#endif
