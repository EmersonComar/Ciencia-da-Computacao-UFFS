-- Criar um usuário para o banco a ser criado
-- Criar um banco de dados e colocar o usuário criado como owner
-- Acessar o banco criado e rodar o script
-- Depois chamar o procedimento call_all com a quantidade de produtos a
-- serem gerados, a quantidade de clientes e a quantidade de vendas
-- Ex.: call call_all (10000, 500, 5000) -> 10k produtos, 500 clientes e 5K vendas
-- Sugestão dos passos (conectado com usuário root - postgres):
-- create user seller password 'seller';
-- create database sales owner=seller
-- \c sales seller
-- \i SalesGenerator.sql

CREATE TABLE IF NOT EXISTS customer (
        cid serial not null,
        name varchar(30) not null,
        address varchar(40) not null,
        age integer,
        constraint pk_customer primary key (cid)
);				

CREATE TABLE IF NOT EXISTS product (					
	pid serial not null primary key,				
	name varchar(30) not null,					
	pqty  integer not null);

CREATE TABLE IF NOT EXISTS sale (
   sid serial not null primary key,
   cid integer not null,
   sdate date not null,
   address varchar(30),
   constraint fk_customer_sale foreign key (cid) references customer(cid));
   
CREATE TABLE IF NOT EXISTS sale_item (
	sid integer not null,
	pid integer not null,
	sqty integer not null,
	CONSTRAINT pk_sale_item PRIMARY KEY (sid,pid),
	CONSTRAINT fk_sale_item_sale FOREIGN KEY (sid) REFERENCES sale(sid),
	CONSTRAINT fk_sale_item_product FOREIGN KEY (pid) REFERENCES product(pid)
);

create or replace procedure ins_product(qttup int ) Language plpgsql
as $$
declare
   prd_tup product%rowtype;
   counter int:=0;
   stock int[5]:='{3,5,8,10,15}';
begin
   raise notice 'Range ids: %',100*qttup;
   -- Or stock:=Array[3,5,8,10,15];
   loop
      --prd_tup.pid:=(random()*100*qttup)::int;
      prd_tup.name:='Product '||counter+1;
      prd_tup.pqty:=stock[(random()*4)::int+1];
      --raise notice 'product: %',prd_tup;
      if (not exists (select 1 from product where pid=prd_tup.pid))
      then
        insert into product (name,pqty) values (prd_tup.name,prd_tup.pqty);
        counter:=counter+1;
      end if;
      exit when counter >= qttup;
   end loop;
end; $$;
--
create or replace procedure ins_customer(qttup int ) Language plpgsql
as $$
declare
   cus_tup customer%rowtype;
   counter int:=0;
begin
   loop
      --prd_tup.pid:=(random()*100*qttup)::int;
      cus_tup.name:='Customer '||counter+1;
      cus_tup.address:=left(MD5(random()::text),20);
      cus_tup.age=(random()*80)::int+20;
      --raise notice 'product: %',prd_tup;
      insert into customer (name,address,age) values (cus_tup.name,cus_tup.address, cus_tup.age);
      counter:=counter+1;
      exit when counter >= qttup;
   end loop;
end; $$;
--
--
create or replace procedure ins_item (sid int) language plpgsql
as $$
declare
    itBySale int[6]:='{2,4,7,8,9,10}';
    nprod int;
    counter_nprod int := 0;
    sale_item_tup sale_item%rowtype;
    array_prod int[];
    qt_prod int;
begin

    select array_agg(pid) into array_prod from product;
    select count(pid) into qt_prod from product;

    -- quantos produtos serão cadastrados por venda
    sale_item_tup.sid := sid;
    --raise notice 'Sale ID: %',sale_item_tup.sid;
    --executa nprod vezes (vindo de itBySale)
    loop
      -- seleciona um pid e um sqty
      sale_item_tup.pid := array_prod[(random()*(qt_prod-1))::int+1];
      --raise notice 'Product ID: % %',sale_item_tup.sid, sale_item_tup.pid;
      nprod := itBySale[(random()*5)::int+1];
      sale_item_tup.sqty := (random()*10)::int;
      if (not exists (select 1 from sale_item si where si.sid=sale_item_tup.sid and si.pid=sale_item_tup.pid))
      then
         insert into sale_item (sid, pid, sqty) values (sale_item_tup.sid, sale_item_tup.pid, sale_item_tup.sqty);
         counter_nprod := counter_nprod + 1;
      end if;
      exit when counter_nprod > nprod;
    end loop;
end; $$;
--
create or replace procedure ins_sale(qttup int ) Language plpgsql
as $$
declare
   sale_tup sale%rowtype;
   qt_cust int;
   array_cust int[];
   counter int:=0;
begin
   raise notice 'Range ids: %',100*qttup;
   select array_agg(cid) into array_cust from customer;
   select count(cid) into qt_cust from customer;
   raise notice 'Qt: %', qt_cust;
   loop
      --sale_tup.sid:=(random()*100*qttup)::int;
      sale_tup.cid=array_cust[(random()*(qt_cust-1))::int+1];
      --raise notice 'Cid: %', sale_tup.cid;
      sale_tup.sdate:='2023-01-01 00:00:00'::timestamp + random()*(now()-timestamp '2023-01-01 00:00:00');
      sale_tup.address:=left(MD5(random()::text),20);
      --raise notice 'Sale: %',sale_tup;
      insert into sale (cid,sdate,address) values (sale_tup.cid,sale_tup.sdate,sale_tup.address) returning sid into sale_tup.sid;
      call ins_item(sale_tup.sid);
      if (mod(counter,5000)=0) 
      then
         raise notice 'Commit %', (counter/5000)::int;
         commit;
      end if;
      counter:=counter+1;
      exit when counter >= qttup;
   end loop;
end; $$;

create or replace procedure call_all (qtprod int, qtcust int, qtsale int) language plpgsql
as $$
begin
   call ins_product(qtprod);
   call ins_customer(qtcust);
   call ins_sale(qtsale);
end; $$;
