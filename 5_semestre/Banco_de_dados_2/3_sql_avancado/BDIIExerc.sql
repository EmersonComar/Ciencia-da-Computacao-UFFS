create table division (
   iddiv serial not null,
   name varchar(30) not null,
   ssnhead integer null,
   constraint pk_division primary key (iddiv)
);
--
create table dept (
  iddept serial not null,
  name varchar(30) not null,
  nemp integer not null,
  iddiv integer,
  ssnmngr integer null,
  constraint pk_dept primary key (iddept),
  constraint fk_dept_div foreign key (iddiv) references division(iddiv)
);
--
create table employee (
  ssn integer not null,
  name varchar(30) not null,
  salary numeric (10,2) not null,
  iddept integer not null,
  constraint pk_employee primary key (ssn),
  constraint fk_employee_dept foreign key (iddept) references dept(iddept)
);
alter table dept add constraint fk_dept_employee foreign key (ssnmngr) references employee (ssn);
--
alter table division add constraint fk_div_employee foreign key (ssnhead) references employee (ssn);
--
create table career (
  idcar serial not null,
  dscr varchar(20) not null,
  minvalue numeric (10,2) not null,
  maxvalue numeric (10,2) not null,
  constraint pk_career primary key (idcar),
  constraint ck_min_max  check (maxvalue > minvalue)
);
--
create table emp_career (
  ssn integer not null,
  idcar integer not null,
  startdt date not null,
  enddt   date,
  constraint pk_emp_career primary key (ssn, idcar),
  constraint fk_emp_career_emp foreign key (ssn) references employee(ssn),
  constraint fk_emp_career_career foreign key (idcar) references career(idcar)  
);
