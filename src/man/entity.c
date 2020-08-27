#include "entity.h"

// --------------------------------------------------------------
Entity_t m_entities[MAX_ENTITIES];
u8 m_invalid;
Entity_t *m_next_free;
Entity_t *m_entities_end;

/**************************************/
void manEntityInit() { 
  m_next_free = m_entities; 
  m_invalid = E_TYPE_INVALID;
  m_entities_end = m_entities + MAX_ENTITIES;
  cpct_memset(m_next_free, 0, sizeof(m_entities));
}
/**************************************/
Entity_t *manEntityCreate() {
  Entity_t *next = m_next_free;
  m_next_free = next + 1;
  next->type = E_TYPE_DEFAULT;
  return next;
}
/**************************************/
void manEntityForAll(void (*pfunUpdateEntity)(Entity_t *)) {
  Entity_t *e = m_entities;
  while (e->type != E_TYPE_INVALID) {
    pfunUpdateEntity(e++);
  }
}
/**************************************/
void manEntityForAllMatching(
    void (*pfunUpdateEntity)(Entity_t *),
    u8 signature) 
{
  Entity_t *e = m_entities;  
  while (e->type != E_TYPE_INVALID) {
    if ((e->type & signature) == signature)
      pfunUpdateEntity(e);
    e++;
  }
}
/**************************************/
// [E1][E4][E3][f][.][.]
void manEntityDestroy(Entity_t *e) {
  Entity_t *dead_e = e;
  --m_next_free;

  if (dead_e != m_next_free)
    cpct_memcpy(dead_e, m_next_free, sizeof(Entity_t));

  m_next_free->type = E_TYPE_INVALID;
}
/**************************************/
void manEntityDelete(Entity_t *e)
{
  e->type |= E_TYPE_DEAD;
}
/**************************************/
void manEntityUpdate()
{
  Entity_t *e = m_entities;
  while (e->type != E_TYPE_INVALID) {
    if (e->type & E_TYPE_DEAD) {
      manEntityDestroy(e);
    } 
    else {
      ++e;
    }
  }
}
/**************************************/
u8 manEntityAvailable()
{
  return (m_next_free < m_entities_end);
}
