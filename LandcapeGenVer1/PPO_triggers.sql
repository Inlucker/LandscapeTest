--������� ��� �������� �������������
--������ ��� ������� canvas_user
-- ������ ������� ��� ��������...
create or replace function deleteRelatedCanvases()
returns trigger 
as $$
begin
	--RAISE notice 'old = %', (old.id);
	delete from PPO.canvas where user_id = old.id;
	return OLD;
end
$$ language plpgsql;

--drop function  deleteRelatedCanvases();

--������ �������
create or replace trigger tr_deleteRelatedCanvases
before delete
on PPO.users
for each row
when (OLD.role = 'canvas_user')
execute procedure deleteRelatedCanvases();

--DROP trigger tr_deleteRelatedCanvases on PPO.users

--���� �������� tr_deleteRelatedCanvases
--delete from PPO.users where id = 1;

--������ ��� ������� moderator
-- ������ ������� ��� ��������...
create or replace function releaseRelatedUsers()
returns trigger 
as $$
begin
	update PPO.users SET moderator_id = NULL where moderator_id = old.id;
	return OLD;
end
$$ language plpgsql;

--drop function  releaseRelatedUsers();

--������ �������
create or replace trigger tr_releaseRelatedUsers
before delete
on PPO.users
for each row
when (OLD.role = 'moderator')
execute procedure releaseRelatedUsers();

--DROP trigger tr_releaseRelatedUsers on PPO.users

--���� �������� tr_releaseRelatedUsers
--delete from PPO.users where id = 7;