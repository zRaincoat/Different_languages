
-- *** The Lost Letter ***
SELECT type FROM addresses
    WHERE address = "900 Somerville Avenue";

SELECT * FROM addresses WHERE id IN (
    SELECT to_address_id FROM packages
        WHERE address LIKE "2 Fin%");

SELECT * FROM packages
WHERE to_address_id = (
    SELECT id FROM addresses
    WHERE address LIKE "2 Fin%")
AND from_address_id = (
    SELECT id FROM addresses
    WHERE address = "900 Somerville Avenue"
);

-- *** The Devious Delivery ***
SELECT address FROM addresses
WHERE id IN (
    SELECT to_address_id FROM packages
    WHERE from_address_id IS NULL);

SELECT * FROM addresses
WHERE ID IN (
    SELECT address_id FROM scans
    WHERE package_id IN (
        SELECT id FROM packages
        WHERE from_address_id IS NULL)
        AND action = "Drop");

-- *** The Forgotten Gift ***
SELECT name FROM drivers
WHERE id IN (
    SELECT driver_id FROM scans
    WHERE package_id = (
        SELECT id FROM packages
        WHERE from_address_id = (
            SELECT id FROM addresses
            WHERE ADDRESS = "109 Tileston Street"
)));


