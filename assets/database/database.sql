#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------


#------------------------------------------------------------
# Table: customer
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS customer(
        id         Int  Auto_increment  NOT NULL ,
        firstname  Varchar (50) NOT NULL ,
        lastname   Varchar (50) NOT NULL ,
        birth_date Date NOT NULL ,
        archived   Bool NOT NULL
	,CONSTRAINT customer_PK PRIMARY KEY (id)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: address
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS address(
        id           Int  Auto_increment  NOT NULL ,
        type         Int NOT NULL ,
        address_line Varchar (50) NOT NULL ,
        postal_code  Char (5) NOT NULL ,
        city         Varchar (50) NOT NULL ,
        archived     Bool NOT NULL
	,CONSTRAINT address_PK PRIMARY KEY (id)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: item
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS item(
        reference         Varchar (50) NOT NULL ,
        name              Varchar (50) NOT NULL ,
        resuply_threshold Int NOT NULL ,
        quantity          Int NOT NULL ,
        price_ht          Float NOT NULL ,
        vat               Float NOT NULL ,
        archived          Bool NOT NULL
	,CONSTRAINT item_PK PRIMARY KEY (reference)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: customer_address
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS customer_address(
        id         Int NOT NULL ,
        id_address Int NOT NULL
	,CONSTRAINT customer_address_PK PRIMARY KEY (id,id_address)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: staff
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS staff(
        id         Int  Auto_increment  NOT NULL ,
        firstname  Varchar (50) NOT NULL ,
        lastname   Varchar (50) NOT NULL ,
        hire_date  Date NOT NULL ,
        id_address Int NOT NULL ,
        id_staff   Int NULL
	,CONSTRAINT staff_PK PRIMARY KEY (id)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: order__history
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS order__history(
        reference               Varchar (50) NOT NULL ,
        estimated_delivery_date Date NOT NULL ,
        created_at              Datetime NOT NULL ,
        id                      Int NOT NULL ,
        id_staff                Int NOT NULL ,
        id_address              Int NOT NULL ,
        id_address_bill         Int NOT NULL
	,CONSTRAINT order__history_PK PRIMARY KEY (reference)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: order__payment
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS order__payment(
        id             Int  Auto_increment  NOT NULL ,
        payment_method Int NOT NULL ,
        amount         Float NOT NULL ,
        sold_at        Datetime NOT NULL ,
        reference      Varchar (50) NOT NULL
	,CONSTRAINT order__payment_PK PRIMARY KEY (id)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: order__item
#------------------------------------------------------------

CREATE TABLE IF NOT EXISTS order__item(
        reference      Varchar (50) NOT NULL ,
        reference_item Varchar (50) NOT NULL ,
        quantity       Int NOT NULL ,
        price          Float NOT NULL ,
        vat            Float NOT NULL
	,CONSTRAINT order__item_PK PRIMARY KEY (reference,reference_item)
)ENGINE=InnoDB;




ALTER TABLE customer_address
	ADD CONSTRAINT customer_address_customer0_FK
	FOREIGN KEY (id)
	REFERENCES customer(id);

ALTER TABLE customer_address
	ADD CONSTRAINT customer_address_address1_FK
	FOREIGN KEY (id_address)
	REFERENCES address(id);

ALTER TABLE staff
	ADD CONSTRAINT staff_address0_FK
	FOREIGN KEY (id_address)
	REFERENCES address(id);

ALTER TABLE staff
	ADD CONSTRAINT staff_staff1_FK
	FOREIGN KEY (id_staff)
	REFERENCES staff(id);

ALTER TABLE order__history
	ADD CONSTRAINT order__history_customer0_FK
	FOREIGN KEY (id)
	REFERENCES customer(id);

ALTER TABLE order__history
	ADD CONSTRAINT order__history_staff1_FK
	FOREIGN KEY (id_staff)
	REFERENCES staff(id);

ALTER TABLE order__history
	ADD CONSTRAINT order__history_address2_FK
	FOREIGN KEY (id_address)
	REFERENCES address(id);

ALTER TABLE order__history
	ADD CONSTRAINT order__history_address3_FK
	FOREIGN KEY (id_address_bill)
	REFERENCES address(id);

ALTER TABLE order__payment
	ADD CONSTRAINT order__payment_order__history0_FK
	FOREIGN KEY (reference)
	REFERENCES order__history(reference);

ALTER TABLE order__item
	ADD CONSTRAINT order__item_order__history0_FK
	FOREIGN KEY (reference)
	REFERENCES order__history(reference);

ALTER TABLE order__item
	ADD CONSTRAINT order__item_item1_FK
	FOREIGN KEY (reference_item)
	REFERENCES item(reference);
