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
Entity_t *manEntityClone(Entity_t *e_src) {
  Entity_t *e_clone = manEntityCreate();
  cpct_memcpy(e_clone, e_src, sizeof(Entity_t));
  return e_clone;
}
/**************************************/
void manEntityForAll(UpdateEntityFn_t fnUpdateEntity) {
  Entity_t *e = m_entities;
  while (e->type != E_TYPE_INVALID) {
    fnUpdateEntity(e++);
  }
}
/**************************************/
void manEntityForAllMatching(
    UpdateEntityFn_t fnUpdateEntity,
    u8               signature) 
{
  Entity_t *e = m_entities;  
  while (e->type != E_TYPE_INVALID) {
    if ((e->type & signature) == signature)
      fnUpdateEntity(e);
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
